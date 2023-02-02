// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickable.h"
#include "Sound/SoundCue.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	HandGun     UMETA(DisplayName = "HandGun"),
	SemiAuto      UMETA(DisplayName = "SemiAuto"),
	Auto   UMETA(DisplayName = "Auto"),
	Pulse   UMETA(DisplayName = "Pulse"),
	Sniper   UMETA(DisplayName = "Sniper"),
  };

UCLASS(Abstract)
class GT3_PROJECT5_GR1_API AWeapon : public AActor
{
	GENERATED_BODY()
	

public:
	AWeapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void Shoot(FVector End, AActor* Actor = nullptr);
	void Reload(int Amount);
	
	bool HasAmmunitionLeft() const { return Ammunition > 0; }
	UFUNCTION(BlueprintCallable)
	int GetAmmunition() const { return Ammunition; }
	UFUNCTION(BlueprintCallable)
	int GetMaxAmmunition() const { return MaxAmmunition; }

	class UArrowComponent* GetSpawnBullet() const { return SpawnBullet; }

	float GetRecoil() const { return Recoil; }
	int GetPulseBullets() const { return PulseBullets; }
	float GetCooldown() const { return Cooldown; }

	void SetActivePickable(bool isActive);
	
	EWeaponType GetWeaponType() const { return WeaponType; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture* Image;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundCue* SoundCue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundCue* ReloadCue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundCue* EmptyCue;

	UPROPERTY()
	bool bIsRecoiling;

protected:
	UFUNCTION()
	void OnPickup(AGT3_Project5_Gr1Character* Player);

	UPROPERTY()
	class UPickable* Pickable;

	UPROPERTY()
	class AGT3_Project5_Gr1Character* Player;

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* VisualMesh;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* SpawnBullet;

	UPROPERTY(EditAnywhere)
	float Damage = 50;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere)
	int MaxAmmunition;
	UPROPERTY()
	int Ammunition;

	UPROPERTY(EditAnywhere)
	float MaxRecoil;
	UPROPERTY()
	float Recoil;
	UPROPERTY()
	float RecoilRecovery;

	UPROPERTY(EditAnywhere)
	int PulseBullets;

	UPROPERTY(EditAnywhere)
	float Cooldown;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponType WeaponType;
};

