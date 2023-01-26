// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "GameLevel.generated.h"

/**
 * 
 */
UCLASS()
class GT3_PROJECT5_GR1_API AGameLevel : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> Hud;
};
