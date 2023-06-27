// Fill out your copyright notice in the Description page of Project Settings.


#include "Escena.h"
#include "EscenaState.h"
#include "EscenaBasico.h"
#include "EscenaAvanzado.h"

// Sets default values
AEscena::AEscena()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


    MeshEscena = CreateDefaultSubobject<UStaticMeshComponent>("Escenario Mesh");
    RootComponent = MeshEscena;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> Escenarios(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane'"));
    if (Escenarios.Succeeded())
    {
        MeshEscena->SetStaticMesh(Escenarios.Object);
        MeshEscena->SetRelativeLocation(FVector(1000.0f, 1000.0f, 1000.0f));
        MeshEscena->SetWorldScale3D(FVector(5.0f, 3.0f, 2.5f));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("mesh not found"));
    }

    materialEscenaBasico = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/Mesh/tetrisBasico_Mat.tetrisBasico_Mat'"));
}

// Called when the game starts or when spawned
void AEscena::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEscena::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AEscena* AEscena::iniciar()
{
    StateBasico = GetWorld()->SpawnActor<AEscenaBasico>(AEscenaBasico::StaticClass());
    StateBasico->SetEscenario(this);

    StateAvanzado = GetWorld()->SpawnActor<AEscenaAvanzado>(AEscenaAvanzado::StaticClass());
    StateAvanzado->SetEscenario(this);


    FTransform SpawnLocation;
    AEscena* Escena = GetWorld()->SpawnActor<AEscena>(AEscena::StaticClass(), SpawnLocation);
    Escena->MeshEscena->SetMaterial(0, materialEscenaBasico);

    Escena->SetActorRelativeLocation(FVector(260.0, -25.0, 100.0));
    Escena->SetActorRelativeRotation(FRotator(0.0, 90.0, 90.0));

    State = StateBasico;
    return Escena;
}

void AEscena::cambiarEscenario(AEscena* _Escenario)
{
    State->EstablecerEscenario(_Escenario);
}

void AEscena::cambiarEstado(IEscenaState* _Estado)
{
    State = _Estado;
}

IEscenaState* AEscena::getEstadoBasico()
{
	return StateBasico;
}

IEscenaState* AEscena::getEstadoAvanzado()
{
	return StateAvanzado;
}

IEscenaState* AEscena::getEstado()
{
	return State;
}
