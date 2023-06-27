// Fill out your copyright notice in the Description page of Project Settings.


#include "PiezaFacade.h"

// Sets default values
APiezaFacade::APiezaFacade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Der = CreateDefaultSubobject<APiezaDer>(TEXT("PiezaDer"));
	Izq = CreateDefaultSubobject<APiezaIzq>(TEXT("PiezaIzq"));
}

void APiezaFacade::SpawnDerBlocks()
{
	Der->CrearPiezaDer();
}

void APiezaFacade::SpawnIzqBlocks()
{
	Izq->CrearPiezaIzq();
}