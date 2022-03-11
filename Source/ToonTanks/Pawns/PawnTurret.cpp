// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"


// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::HandleDestruction() 
{
    Super::HandleDestruction();
    Destroy();
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!PlayerPawn || DistanceToPlayer() > FireRange) {
        return;
    }

    RotateTurret(PlayerPawn->GetActorLocation());

}

void APawnTurret::CheckFireCondition() 
{
    // Check if player exists/still alive
    if (!PlayerPawn) {
        UE_LOG(LogTemp, Warning, TEXT("Fire Condition checked: found no reference to PlayerPawn"));
        return;
    }

    if (!PlayerPawn->GetPlayerAlive()) {
        UE_LOG(LogTemp, Warning, TEXT("Fire Condition checked: player is dead."));
        return;
    }

    // Check if player is within firing range
    if (DistanceToPlayer() <= FireRange) {
        UE_LOG(LogTemp, Warning, TEXT("Fire Condition checked: player is within range."));
        Fire();
    }
}

float APawnTurret::DistanceToPlayer() 
{
    if (!PlayerPawn) {
        return 0.f;
    }

    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}
