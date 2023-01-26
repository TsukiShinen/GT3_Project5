// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLevel.h"

#include "Blueprint/UserWidget.h"

void AGameLevel::BeginPlay()
{
	Super::BeginPlay();	
	CreateWidget<UUserWidget>(GetWorld(), Hud)->AddToViewport();
}
