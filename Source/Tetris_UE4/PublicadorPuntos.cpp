// Fill out your copyright notice in the Description page of Project Settings.


#include "PublicadorPuntos.h"

APublicadorPuntos::APublicadorPuntos()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APublicadorPuntos::BeginPlay()
{
	Super::BeginPlay();
}

void APublicadorPuntos::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APublicadorPuntos::EstablecerPuntos(int _Puntos)
{
	Puntos = _Puntos;
	PuntosCambiados();
}

void APublicadorPuntos::PuntosCambiados()
{
	Notificar();
}
