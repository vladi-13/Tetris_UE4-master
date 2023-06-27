// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Publicador.h"
#include "PublicadorPuntos.generated.h"

/**
 * 
 */
UCLASS()
class TETRIS_UE4_API APublicadorPuntos : public APublicador
{
	GENERATED_BODY()
	
public:
	APublicadorPuntos();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	int Puntos;
	void EstablecerPuntos(int _Puntos);
	void PuntosCambiados();
	FORCEINLINE int ObtenerPuntos() { return Puntos; }
};
