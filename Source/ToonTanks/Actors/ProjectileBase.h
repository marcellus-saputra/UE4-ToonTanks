// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;


UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	private:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* ProjectileMovement;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* ProjectileMesh;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UDamageType> DamageType;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* TrailParticle;

		UPROPERTY(EditAnywhere, Category = "Movement")
		float ProjectileSpeed = 1300.f;

		UPROPERTY(EditAnywhere, Category = "Damage")
		float Damage = 50.f;

		UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* ImpactParticle;

		UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* HitSound;

		UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* LaunchSound;

		UPROPERTY(EditAnywhere, Category = "Effects")
		TSubclassOf<UMatineeCameraShake> HitShake;

		UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	public:	
		// Sets default values for this actor's properties
		AProjectileBase();

};
