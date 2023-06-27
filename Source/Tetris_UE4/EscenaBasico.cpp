// Fill out your copyright notice in the Description page of Project Settings.


#include "EscenaBasico.h"
#include "Escena.h"

// Sets default values
AEscenaBasico::AEscenaBasico()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	materialEscenaBasico = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/Mesh/tetrisBasico_Mat.tetrisBasico_Mat'"));

}

// Called when the game starts or when spawned
void AEscenaBasico::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEscenaBasico::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEscenaBasico::EstablecerEscenario(AEscena* _Escenario)
{
    _Escenario->MeshEscena->SetMaterial(0, materialEscenaBasico);
    Escena->cambiarEstado(Escena->getEstadoAvanzado());
}

void AEscenaBasico::SetEscenario(AEscena* _Escenario)
{
	Escena = _Escenario;
}

