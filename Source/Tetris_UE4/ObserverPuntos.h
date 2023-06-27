// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Suscriptor.h"
#include "ObserverPuntos.generated.h"

/**
 * 
 */
UCLASS()
class TETRIS_UE4_API AObserverPuntos : public AActor , public ISuscriptor
{
	GENERATED_BODY()
public:
	AObserverPuntos();
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;
	virtual void Actualizar(class APublicador* Publicador) override;
	void EstablecerPublicador(class APublicadorPuntos* _PublicadorPuntos);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		class APublicadorPuntos* PublicadorPuntos;
};
