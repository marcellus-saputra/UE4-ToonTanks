// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ToonTanksGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UToonTanksGameInstance : public UGameInstance
{
	public:
		UPROPERTY(EditDefaultsOnly, Category="Level Management")
		int32 CurrentLevel = 0;

		UPROPERTY(EditDefaultsOnly, Category="Level Management")
		TArray<FName> LevelArray;
	GENERATED_BODY()
	
};
