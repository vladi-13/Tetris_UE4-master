// Fill out your copyright notice in the Description page of Project Settings.


#include "EscenaAvanzado.h"
#include "Escena.h"

// Sets default values
AEscenaAvanzado::AEscenaAvanzado()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	materialEscenaAvanzado = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/Mesh/tetrisAvanzado_Mat.tetrisAvanzado_Mat'"));

}

// Called when the game starts or when spawned
void AEscenaAvanzado::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEscenaAvanzado::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEscenaAvanzado::EstablecerEscenario(AEscena* _Escenario)
{
	_Escenario->MeshEscena->SetMaterial(0, materialEscenaAvanzado);
	Escena->cambiarEstado(Escena->getEstadoBasico());
}

void AEscenaAvanzado::SetEscenario(AEscena* _Escenario)
{
	Escena = _Escenario;
}

