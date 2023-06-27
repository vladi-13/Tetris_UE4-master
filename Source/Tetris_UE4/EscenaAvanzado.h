// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EscenaState.h"
#include "EscenaAvanzado.generated.h"

UCLASS()
class TETRIS_UE4_API AEscenaAvanzado : public AActor , public IEscenaState
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEscenaAvanzado();

private:

	UPROPERTY()
		class AEscena* Escena;

	UMaterialInterface* materialEscenaAvanzado;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	virtual void EstablecerEscenario(class AEscena* _Escenario) override;
	virtual void SetEscenario(class AEscena* _Escenario) override;

};
