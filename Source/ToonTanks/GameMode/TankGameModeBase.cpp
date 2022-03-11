// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

void ATankGameModeBase::BeginPlay() 
{
    Super::BeginPlay();

    HandleGameStart();
}

void ATankGameModeBase::HandleGameStart() 
{
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
    NumberOfTurrets = TurretActors.Num();

    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

    GameStart();

    if (PlayerControllerRef) {
        PlayerControllerRef->SetPlayerEnabledState(false);
        FTimerHandle PlayerEnableHandle;
        FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);
        UE_LOG(LogTemp, Warning, TEXT("Get Ready..."));
        GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
    } else {
        UE_LOG(LogTemp, Error, TEXT("PlayerControllerRef not found!"));
    }
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) 
{
    if (PlayerControllerRef) {
        PlayerControllerRef->SetPlayerEnabledState(false);
    }
    PlayerTank->SetActorTickEnabled(false);
    GameOver(PlayerWon);
}

void ATankGameModeBase::ActorDied(AActor* DeadActor) 
{
    if (DeadActor == PlayerTank) {
        PlayerTank->HandleDestruction();
        HandleGameOver(false);
    } else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor)) {
        DestroyedTurret->HandleDestruction();
        NumberOfTurrets -= 1;
        if (NumberOfTurrets == 0) {
            HandleGameOver(true);
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("%s: Died"), *DeadActor->GetName());
}
