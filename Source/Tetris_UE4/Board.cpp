// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "Pieces.h"
#include "Escena.h"
#include "PiezaFacade.h"
#include "PublicadorPuntos.h"
#include "ObserverPuntos.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ABoard::ABoard()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    GameOver = 0;

    Puntos = 0;
    BloquesEliminados = 0;
    LineasEliminadas = 0;
    PiezasUsadas = 0;

    static ConstructorHelpers::FObjectFinder<USoundCue> LineRemove_Sound(TEXT("SoundCue'/Game/Sounds/line-remove_Cue.line-remove_Cue'"));
    if (LineRemove_Sound.Succeeded())
    {
        LineRemoveSoundCue = LineRemove_Sound.Object;
    }

    static ConstructorHelpers::FObjectFinder<USoundCue> MoveToEnd_Sound(TEXT("SoundCue'/Game/Sounds/force-hit_Cue.force-hit_Cue'"));
    if (MoveToEnd_Sound.Succeeded())
    {
        MoveToEndSoundCue = MoveToEnd_Sound.Object;
    }

    static ConstructorHelpers::FObjectFinder<USoundCue> GameStart_Sound(TEXT("SoundCue'/Game/Sounds/start_Cue.start_Cue'"));
    if (GameStart_Sound.Succeeded())
    {
        GameStartSoundCue = GameStart_Sound.Object;
    }

    static ConstructorHelpers::FObjectFinder<USoundCue> GameOver_Sound(TEXT("SoundCue'/Game/Sounds/gameover_Cue.gameover_Cue'"));
    if (GameOver_Sound.Succeeded())
    {
        GameOverSoundCue = GameOver_Sound.Object;
    }
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
    Super::BeginPlay();

    Escenario = GetWorld()->SpawnActor<AEscena>(AEscena::StaticClass());
    Escen = Escenario->iniciar();

    PublicadorPuntos = GetWorld()->SpawnActor<APublicadorPuntos>(APublicadorPuntos::StaticClass());
    Observador = GetWorld()->SpawnActor<AObserverPuntos>(AObserverPuntos::StaticClass());
    Observador->EstablecerPublicador(PublicadorPuntos);
    for (TActorIterator<APieces> it(GetWorld()); it; ++it)
    {
        if (it->GetFName() == TEXT("DissmissPieces"))
        {
            it->Dismiss();
            it->Destroy();
        }
    }
}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bGameOver)
    {
        return;
    }

    switch (Status)
    {
    case PS_NOT_INITED:
        iniciarPiezas();
        CoolLeft = CoolDown;
        Status = PS_MOVING;
        break;
    case PS_MOVING:
        CoolLeft -= DeltaTime;
        if (CoolLeft <= 0.0f)
        {
            MoveDown();
        }
        break;
    case PS_GOT_BOTTOM:
        NextNextPieces->DeletePiece();
        NextPieces->DeletePiece();
        CoolLeft -= DeltaTime;
        if (CoolLeft <= 0.0f)
        {
            if (CurrentPieces)
            {
                CurrentPieces->Dismiss();
                CurrentPieces->Destroy();
            }
            NewPieces();
            CoolLeft = CoolDown;
            Status = PS_MOVING;
        }
        break;
    default:
        break;
    }
}

// Called to bind functionality to input
void ABoard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction("Rotate", IE_Pressed, this, &ABoard::Rotate);
    PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &ABoard::MoveLeft);
    PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ABoard::MoveRight);
    PlayerInputComponent->BindAction("MoveDownToEnd", IE_Pressed, this, &ABoard::MoveDownToEnd);
    PlayerInputComponent->BindAction("Modalidad", IE_Pressed, this, &ABoard::Modalidad);
}

void ABoard::Rotate()
{
    if (CurrentPieces && Status != PS_GOT_BOTTOM)
    {
        CurrentPieces->TestRotate();
    }
}

void ABoard::MoveLeft()
{
    if (CurrentPieces)
    {
        CurrentPieces->MoveLeft();
        if (Status == PS_GOT_BOTTOM)
        {
            MoveDownToEnd();
        }
    }
}

void ABoard::MoveRight()
{
    if (CurrentPieces)
    {
        CurrentPieces->MoveRight();
        if (Status == PS_GOT_BOTTOM)
        {
            MoveDownToEnd();
        }
    }
}

void ABoard::MoveDown()
{
    if (CurrentPieces)
    {
        if (!CurrentPieces->MoveDown())
        {
            Status = PS_GOT_BOTTOM;
        }
        CoolLeft = CoolDown;
    }
}

void ABoard::NewPieces()
{
    CheckLine();
    if (CurrentPieces)
    {
        CurrentPieces->Dismiss();
        CurrentPieces->Destroy();
    }
    CurrentPieces = GetWorld()->SpawnActor<APieces>(FVector(0.0f, 5.0f, 195.0f), FRotator::ZeroRotator);
    CurrentPieces->SpawnBlocks(NextPieces->GetCoordenadas());
    if (NextPieces)
    {
        NextPieces->Dismiss();
        NextPieces->Destroy();
    }
    NextPieces = GetWorld()->SpawnActor<APieces>(FVector(0.0f, 125.0f, 150.0f), FRotator::ZeroRotator);
    NextPieces->SpawnBlocks(NextNextPieces->GetCoordenadas());
    if (NextNextPieces)
    {
        NextNextPieces->Dismiss();
        NextNextPieces->Destroy();
    }
    NextNextPieces = GetWorld()->SpawnActor<APieces>(FVector(0.0f, 125.0f, 75.0f), FRotator::ZeroRotator);
    NextNextPieces->SpawnBlocks();
    bGameOver = CheckGameOver();
    if (bGameOver)
    {
        GameOver = 1;
        UE_LOG(LogTemp, Warning, TEXT("Game Over!!!!!!!!"));
        if (GameOverSoundCue)
        {
            UGameplayStatics::PlaySoundAtLocation(GetWorld(), GameOverSoundCue, GetActorLocation(), GetActorRotation());
        }
    }
    PiezasUsadas++;
    PublicadorPuntos->EstablecerPuntos(GetPiezasUsadas());
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Piezas Usadas: %d"), PublicadorPuntos->ObtenerPuntos()));
}

void ABoard::CheckLine()
{
    auto MoveDownFromLine = [this](int z) {
        FVector Location(0.0f, 0.0f, 5.0 * z + 100.0);
        FRotator Rotation(0.0f, 0.0f, 0.0f);
        TArray<struct FOverlapResult> OutOverlaps;
        FCollisionShape CollisionShape;
        FVector Extent(4.5f, 49.5f, 95.0 + 4.5 - 5.0 * z);
        CollisionShape.SetBox(Extent);
        DrawDebugBox(GetWorld(), Location, Extent, FColor::Purple, false, 1, 0, 1);
        FCollisionQueryParams Params;
        FCollisionResponseParams ResponseParam;
        if (GetWorld()->OverlapMultiByChannel(OutOverlaps,
            Location, Rotation.Quaternion(), ECollisionChannel::ECC_WorldDynamic,
            CollisionShape, Params, ResponseParam))
        {
            for (auto&& Result : OutOverlaps)
            {
                FVector NewLocation = Result.GetActor()->GetActorLocation();
                NewLocation.Z -= 10.0f;
                Result.GetActor()->SetActorLocation(NewLocation);
            }
        }
    };

    int z = 0;
    while (z < 20)
    {
        FVector Location(0.0f, 0.0f, 10.0f * z + 5.0f);
        FRotator Rotation(0.0f, 0.0f, 0.0f);
        TArray<struct FOverlapResult> OutOverlaps;
        FCollisionShape CollisionShape;
        CollisionShape.SetBox(FVector(4.0f, 49.0f, 4.0f));
        //DrawDebugBox(GetWorld(), Location, FVector(4.5f, 49.5f, 4.5f), FColor::Purple, false, 1, 0, 1);
        FCollisionQueryParams Params;
        FCollisionResponseParams ResponseParam;
        bool b = GetWorld()->OverlapMultiByChannel(OutOverlaps,
            Location, Rotation.Quaternion(), ECollisionChannel::ECC_WorldDynamic,
            CollisionShape, Params, ResponseParam);
        if (!b || OutOverlaps.Num() < 10)
        {
            ++z;
            continue;
        }
        else // this line is full, remove the line
        {
            UE_LOG(LogTemp, Warning, TEXT("Find FULL LINE at z=%d"), z);
            for (auto&& Result : OutOverlaps)
            {
                Result.GetActor()->Destroy();
            }
            MoveDownFromLine(z);
            Puntos += 100;
            PublicadorPuntos->EstablecerPuntos(GetPuntos());
            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Puntos: %d"), PublicadorPuntos->ObtenerPuntos()));
            BloquesEliminados += 10;
            PublicadorPuntos->EstablecerPuntos(GetBloquesEliminados());
            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Bloques Eliminados: %d"), PublicadorPuntos->ObtenerPuntos()));
            LineasEliminadas++;
            PublicadorPuntos->EstablecerPuntos(GetLineasEliminadas());
            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Lineas Eliminadas: %d"), PublicadorPuntos->ObtenerPuntos()));
            Escenario->cambiarEscenario(Escen);
            if (LineRemoveSoundCue)
            {
                UGameplayStatics::PlaySoundAtLocation(GetWorld(), LineRemoveSoundCue, GetActorLocation(), GetActorRotation());
            }
        }
    }
}

void ABoard::MoveDownToEnd()
{
    if (!CurrentPieces)
    {
        return;
    }

    while (CurrentPieces->MoveDown())
    {
    }

    if (MoveToEndSoundCue)
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), MoveToEndSoundCue, GetActorLocation(), GetActorRotation());
    }

    switch (Status)
    {
    case PS_MOVING:
        Status = PS_GOT_BOTTOM;
        CoolLeft = CoolDown;
        break;
    case PS_GOT_BOTTOM:
        break;
    default:
        UE_LOG(LogTemp, Warning, TEXT("Wrong status for MoveDownToEnd"));
        break;
    }
}

void ABoard::Modalidad()
{
    GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, TEXT("Cambiando Modalidad"));
    PiezaFacade = GetWorld()->SpawnActor<APiezaFacade>(APiezaFacade::StaticClass());
    PiezaFacade->SpawnDerBlocks();
    PiezaFacade->SpawnIzqBlocks();
}

bool ABoard::CheckGameOver()
{
    if (!CurrentPieces)
    {
        UE_LOG(LogTemp, Warning, TEXT("NoPieces"));
        return true;
    }

    return CurrentPieces->CheckWillCollision([](FVector OldVector) { return OldVector; });
}

void ABoard::iniciarPiezas()
{
    CurrentPieces = GetWorld ()->SpawnActor<APieces>(FVector(0.0f, 5.0f, 195.0f), FRotator::ZeroRotator);
    CurrentPieces->SpawnBlocks();
    NextPieces = GetWorld()->SpawnActor<APieces>(FVector(0.0f, 125.0f, 150.0f), FRotator::ZeroRotator);
    NextPieces->SpawnBlocks();
    NextNextPieces = GetWorld()->SpawnActor<APieces>(FVector(0.0f, 125.0f, 75.0f), FRotator::ZeroRotator);
    NextNextPieces->SpawnBlocks();
}