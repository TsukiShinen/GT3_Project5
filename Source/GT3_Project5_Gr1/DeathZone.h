// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "DeathZone.generated.h"

UCLASS()
class GT3_PROJECT5_GR1_API ADeathZone : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADeathZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerBox;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
