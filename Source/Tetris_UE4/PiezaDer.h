// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Block.h"
#include "GameFramework/Actor.h"
#include "PiezaDer.generated.h"

UCLASS()
class TETRIS_UE4_API APiezaDer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APiezaDer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void CrearPiezaDer();

	UPROPERTY()
		TArray<class UMaterial*> Colors;

private:
	TArray<ABlock*> Blocks;

};
