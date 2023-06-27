// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.h"
#include "PiezaIzq.generated.h"

UCLASS()
class TETRIS_UE4_API APiezaIzq : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APiezaIzq();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void CrearPiezaIzq();

	UPROPERTY()
		TArray<class UMaterial*> Colors;

private:
	TArray<ABlock*> Blocks;
};
