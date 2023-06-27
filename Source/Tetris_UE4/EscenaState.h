// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EscenaState.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEscenaState : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TETRIS_UE4_API IEscenaState
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void EstablecerEscenario(class AEscena* _Escenario) = 0;
	virtual void SetEscenario(class AEscena* Escenario) = 0;
};
