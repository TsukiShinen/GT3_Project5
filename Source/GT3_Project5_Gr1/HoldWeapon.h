// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
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

	void SetAnimInstance(UAnimInstance* NewAnimInstance) { AnimInstance = NewAnimInstance; }
	void SwitchWeapon(AWeapon* NewWeapon, AWeapon* SecondWeapon = nullptr);

	void Aim(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);
	void ShootAuto(const FInputActionValue& Value);
	void EndAim(const FInputActionValue& Value);
	void Reload(const FInputActionValue& Value);
	UFUNCTION()
	void EndShoot(const FInputActionValue& Value);
	UFUNCTION()
	void EndReload();

	DECLARE_EVENT(UHoldWeapon, FAimingStart)
	FAimingStart& OnStartAim() { return AimingStartEvent; }

	DECLARE_EVENT(UHoldWeapon, FAimingEnd)
	FAimingEnd& OnEndAim() { return AimingEndEvent; }
	
	DECLARE_EVENT(UHoldWeapon, FSniping)
	FSniping& OnSniping() { return SnipingEvent; }

	FAimingStart AimingStartEvent;
	FAimingEnd AimingEndEvent;
	FSniping SnipingEvent;

	UAnimMontage* GetShootMontage() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ReloadAction;

	UPROPERTY()
	AWeapon* Weapon;

	UPROPERTY(EditAnywhere)
	UAnimMontage* ShootMontage;
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* ShootHandGunMontage;

	UPROPERTY(EditAnywhere)
	UAnimMontage* ReloadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asset References")
	UNiagaraSystem* ShootParticles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asset References")
	UNiagaraSystem* HitParticles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asset References")
	UNiagaraSystem* HitOnEnemyParticles;

	UPROPERTY()
	bool bIsAiming;

	UPROPERTY()
	bool bIsShooting;

	UPROPERTY(BlueprintReadOnly)
	bool bIsReloading;

	UPROPERTY(VisibleAnywhere)
	UAnimInstance* AnimInstance;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* ActionDecalToSpawn;

	// Called when the game starts
	virtual void BeginPlay() override;

	void PlayAnimAim() const { AnimInstance->Montage_Play(GetShootMontage()); }

	void PlayAnimShoot() const
	{
		AnimInstance->Montage_Play(GetShootMontage());
		AnimInstance->Montage_JumpToSection(TEXT("Shoot"), GetShootMontage());
	}

	void PlayAnimReload() const { AnimInstance->Montage_Play(ReloadMontage); }
	void StopAnimAimAndShoot() const { AnimInstance->Montage_Stop(.5f, GetShootMontage()); }

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY()
	int IndexPulse = 0;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> SniperHud;

	UPROPERTY()
	UUserWidget* SniperWidget;

	FTimerHandle ShootCooldownHandler;
	FTimerDelegate ShootCooldownDelegate;
};
