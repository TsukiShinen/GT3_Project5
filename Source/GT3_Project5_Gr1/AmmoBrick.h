// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GT3_Project5_Gr1Character.h"
#include "GameFramework/Actor.h"
#include "AmmoBrick.generated.h"

UCLASS()
class GT3_PROJECT5_GR1_API AAmmoBrick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoBrick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnPickup(AGT3_Project5_Gr1Character* Player);

	UPROPERTY()
	UPickable* Pickable;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;

	UPROPERTY(EditAnywhere)
	int AmmoAmount = 50;
};
