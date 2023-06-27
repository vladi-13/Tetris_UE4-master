// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EscenaState.h"
#include "Escena.generated.h"

UCLASS()
class TETRIS_UE4_API AEscena : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEscena();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
		IEscenaState* State;
		IEscenaState* StateBasico;
		IEscenaState* StateAvanzado;

public:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshEscena;

	UMaterialInterface* materialEscenaBasico;

	AEscena* iniciar();
	void cambiarEscenario(AEscena* _Escenario);
	void cambiarEstado(IEscenaState* _Estado);

	IEscenaState* getEstadoBasico();
	IEscenaState* getEstadoAvanzado();
	IEscenaState* getEstado();

};
