// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemySkeleton.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class GT3_PROJECT5_GR1_API ASpawner : public AActor
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpawn);

public:
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SetActive(const bool bActive) { bIsActive = bActive;}
	
	UPROPERTY()
	FOnSpawn OnSpawn;

private:
	UFUNCTION()
	void Spawn();

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Triggerbox;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* VisualMesh;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemySkeleton> Enemy;

	UPROPERTY(EditAnywhere)
	float SpawnCooldown;

	FTimerHandle Handle;
	FTimerDelegate Delegate;

	bool Spawning = false;

	bool bIsActive = true;
};
