// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
	/*
	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* SkeletalMesh;*/


	bool IsAlive = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};