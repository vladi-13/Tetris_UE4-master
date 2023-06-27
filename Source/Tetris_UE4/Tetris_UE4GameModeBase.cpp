// Fill out your copyright notice in the Description page of Project Settings.


#include "Tetris_UE4GameModeBase.h"
#include "Board.h"
#include "Pieces.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Sound/SoundCue.h"

ATetris_UE4GameModeBase::ATetris_UE4GameModeBase()
{
    DefaultPawnClass = ABoard::StaticClass();

    static ConstructorHelpers::FObjectFinder<USoundCue> MusicTetris(TEXT("SoundCue'/Game/Sounds/musicTetris_Cue.musicTetris_Cue'"));
    if (MusicTetris.Succeeded())
    {
		MusicJuego = MusicTetris.Object;
	}
}

void ATetris_UE4GameModeBase::BeginPlay()
{
    Super::BeginPlay();

    if (MusicJuego)
    {
        UGameplayStatics::PlaySound2D(this, MusicJuego);
    }

    for(TActorIterator<ACameraActor> it(GetWorld()); it; ++it)
    {
        //UE_LOG(LogTemp, Warning, TEXT("Find camera: %s"), *(it->GetFName().ToString()));
        if(it->GetFName() == TEXT("BoardCamera"))
        {
            APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
            PC->SetViewTargetWithBlend(*it, 0.5);
            break;
        }
    }
}