// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemySkeleton.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class GT3_PROJECT5_GR1_API ASpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void Spawn();
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* VisualMesh;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemySkeleton> Enemy;
	
	UPROPERTY(EditAnywhere)
	float SpawnCooldown;

	FTimerHandle Handle;
	FTimerDelegate Delegate;
};
