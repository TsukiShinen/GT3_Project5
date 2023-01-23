// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Weapon.h"
#include "Components/ActorComponent.h"
#include "HoldWeapon.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GT3_PROJECT5_GR1_API UHoldWeapon : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHoldWeapon();
	
	void SetupPlayerInputComponent(class UEnhancedInputComponent* EnhancedInputComponent);

	void AttachWeapon(TSubclassOf<AWeapon> WeaponType, USkeletalMeshComponent* Mesh);
	
	void Aim(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);
	void EndAim(const FInputActionValue& Value);
	UFUNCTION()
	void EndShoot();

	DECLARE_EVENT(UHoldWeapon, FAimingStart)
	FAimingStart& OnStartAim() { return AimingStartEvent; }
	
	DECLARE_EVENT(UHoldWeapon, FAimingEnd)
	FAimingEnd& OnEndAim() { return AimingEndEvent; }
	
	FAimingStart AimingStartEvent;
	FAimingEnd AimingEndEvent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AimAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShootAction;
	
	UPROPERTY()
	AWeapon* Weapon;
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* ShootMontage;
	
	UPROPERTY()
	bool bIsAiming;
	
	UPROPERTY()
	bool bIsShooting;

	UPROPERTY(VisibleAnywhere)
	UAnimInstance* AnimInstance;
	
	// Called when the game starts
	virtual void BeginPlay() override;

	void PlayAnimAim() const { AnimInstance->Montage_Play(ShootMontage); }
	void PlayAnimShoot() const { AnimInstance->Montage_Play(ShootMontage); AnimInstance->Montage_JumpToSection(TEXT("Shoot"), ShootMontage); }
	void StopAnimAimAndShoot() const { AnimInstance->Montage_Stop(.5f, ShootMontage); }

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
