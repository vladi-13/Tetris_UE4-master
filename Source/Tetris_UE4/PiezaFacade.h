// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PiezaDer.h"
#include "PiezaIzq.h"
#include "PiezaFacade.generated.h"

UCLASS()
class TETRIS_UE4_API APiezaFacade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APiezaFacade();

	void SpawnDerBlocks();
	void SpawnIzqBlocks();

private:
	UPROPERTY()
		APiezaDer* Der;

	UPROPERTY()
		APiezaIzq* Izq;

};
