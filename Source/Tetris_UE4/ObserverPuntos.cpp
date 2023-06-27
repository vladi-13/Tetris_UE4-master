// Fill out your copyright notice in the Description page of Project Settings.


#include "ObserverPuntos.h"
#include "Publicador.h"
#include "PublicadorPuntos.h"

AObserverPuntos::AObserverPuntos()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AObserverPuntos::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AObserverPuntos::Destroyed()
{
	Super::Destroyed();
	if (!PublicadorPuntos) {
		PublicadorPuntos->Desuscribir(this);
	}
}

void AObserverPuntos::Actualizar(APublicador* Publicador)
{
	//APublicadorPuntos* PublicadorPuntos = Cast<APublicadorPuntos>(Publicador);
	//if (PublicadorPuntos) {
	//	UE_LOG(LogTemp, Warning, TEXT("Puntos: %d"), PublicadorPuntos->ObtenerPuntos());
	//}
}

void AObserverPuntos::EstablecerPublicador(APublicadorPuntos* _PublicadorPuntos)
{
	PublicadorPuntos = _PublicadorPuntos;
	PublicadorPuntos->Suscribir(this);
}

void AObserverPuntos::BeginPlay()
{
	Super::BeginPlay();
}
