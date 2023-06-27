// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Board.h"
#include "Suscriptor.h"
#include "Publicador.generated.h"

UCLASS()
class TETRIS_UE4_API APublicador : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APublicador();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Suscribir(class AActor* _Suscribir);
	virtual void Desuscribir(class AActor* _Desuscribir);
	virtual void Notificar();
private:
	UPROPERTY()
		TArray<class AActor*> Suscriptores = TArray<class AActor*>();
};
