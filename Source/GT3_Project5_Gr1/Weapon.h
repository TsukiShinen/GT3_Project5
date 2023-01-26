// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class GT3_PROJECT5_GR1_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	AWeapon();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	void Shoot(FVector End, AActor* Actor = nullptr);
	void Reload(int Amount);

	bool IsAuto() const { return bIsAuto; }
	
	bool HasAmmunitionLeft() const { return Ammunition > 0; }
	UFUNCTION(BlueprintCallable)
	int GetAmmunition() const { return Ammunition; }
	UFUNCTION(BlueprintCallable)
	int GetMaxAmmunition() const { return MaxAmmunition; }
	
	UArrowComponent* GetSpawnBullet() const { return SpawnBullet; }
	
	float GetRecoil() const { return Recoil; }
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture* Image;

	UPROPERTY()
	bool bIsRecoiling;

protected:
	UPROPERTY()
	class AGT3_Project5_Gr1Character* Player;
	
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* VisualMesh;
	
	UPROPERTY(EditAnywhere)
	UArrowComponent* SpawnBullet;

	UPROPERTY(EditAnywhere)
	bool bIsAuto;

	UPROPERTY(EditAnywhere)
	float Damage = 50;

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
	TSubclassOf<UDamageType> DamageType;
};
