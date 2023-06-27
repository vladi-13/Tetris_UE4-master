// Fill out your copyright notice in the Description page of Project Settings.


#include "Publicador.h"

// Sets default values
APublicador::APublicador()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APublicador::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APublicador::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APublicador::Suscribir(AActor* _Suscribir)
{
	Suscriptores.Add(_Suscribir);
}

void APublicador::Desuscribir(AActor* _Desuscribir)
{
	Suscriptores.Remove(_Desuscribir);
}

void APublicador::Notificar()
{
	for (AActor* Suscriptor : Suscriptores)
	{
		ISuscriptor* Suscrito = Cast<ISuscriptor>(Suscriptor);
		if (Suscriptor)
		{
			//Suscrito->Actualizar(this);
		}
	}
}

