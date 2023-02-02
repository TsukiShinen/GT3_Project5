// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ScoreGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GT3_PROJECT5_GR1_API UScoreGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere)
	int Score = 0;
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetScore(){ return Score; }
	FORCEINLINE void SetScore(int newScore) { Score = newScore ; }
};
