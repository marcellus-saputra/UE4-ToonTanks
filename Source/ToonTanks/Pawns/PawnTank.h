// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

/**
 * 
 */
class USpringArmComponent;
class UCameraComponent;

UCLASS()

class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()

	private:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Speed", meta = (AllowPrivateAccess = "true"))
		float MoveSpeed = 1000.f;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Speed", meta = (AllowPrivateAccess = "true"))
		float TurnRate = 50.f;

		FVector MoveDirection;
		FQuat RotationDirection;
		APlayerController* PlayerController;
		bool bPlayerAlive = true;

		void CalculateMoveInput(float Value);
		void CalculateRotateInput(float Value);

		void Move();
		void Rotate();

	public:
		APawnTank();
		virtual void HandleDestruction() override;

		// Called every frame
		virtual void Tick(float DeltaTime) override;

		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

		bool GetPlayerAlive();
	
	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

};
