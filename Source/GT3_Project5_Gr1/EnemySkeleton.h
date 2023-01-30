// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "EnemySkeleton.generated.h"

UCLASS()
class GT3_PROJECT5_GR1_API AEnemySkeleton : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float MaxLife = 100;

	UPROPERTY(EditAnywhere)
	float Life = 100;

public:
	// Sets default values for this character's properties
	AEnemySkeleton();

	UPROPERTY(VisibleAnywhere)
	bool IsAlive = true;
	UPROPERTY(VisibleAnywhere)
	bool IsAttacking = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere)
	UAnimInstance* AnimInstance;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AM_Skeleton_Attack;

	void PlayAttackAnim() const { AnimInstance->Montage_Play(AM_Skeleton_Attack); }
	void StopAttackAnim() const { AnimInstance->Montage_Stop(0.5f, AM_Skeleton_Attack); }

private:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerBox;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
