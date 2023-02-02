// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLevel.h"
#include "EnhancedInputComponent.h"
#include "ScoreGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "GT3_Project5_Gr1Character.h"

void AGameLevel::BeginPlay()
{
	Super::BeginPlay();
	CreateWidget<UUserWidget>(GetWorld(), Hud)->AddToViewport();

	CurrentZombieSpawned = 0;
	CurrentZombieAlive = 0;
	CurrentPhase = 0;

	for (const auto Spawner : LstSpawner)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("SPAWNER !"));
		Spawner->OnSpawn.AddDynamic(this, &AGameLevel::OnSpawn);
	}
}

void AGameLevel::DeactivateSpawner()
{
	for (const auto Spawner : LstSpawner)
	{
		Spawner->SetActive(false);
	}
}

void AGameLevel::OnSpawn(AEnemySkeleton* EnemySpawned)
{
	CurrentZombieSpawned ++;
	CurrentZombieAlive++;
	
	EnemySpawned->OnDeath.AddDynamic(this, &AGameLevel::OnEnemyDeath);
	if (CurrentZombieSpawned >= ZombiesPerPhase[CurrentPhase])
	{
		DeactivateSpawner();
	}
}

void AGameLevel::ActivateSpawner()
{
	CurrentZombieSpawned = 0;
	CurrentZombieAlive = 0;
	for (const auto Spawner : LstSpawner)
	{
		Spawner->SetActive(true);
	}
}

void AGameLevel::NextPhase()
{
	CurrentPhase++;
	if (CurrentPhase < ZombiesPerPhase.Num())
	{
		ActivateSpawner();
	} else
	{
		auto Player = Cast<AGT3_Project5_Gr1Character>(GetWorld()->GetFirstPlayerController()->GetPawn());
		auto GI = Cast<UScoreGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		
		GI->SetScore(Player->GetScore());
		
		UGameplayStatics::OpenLevel(GetWorld(), "EndMenu");
	}
}

void AGameLevel::OnEnemyDeath()
{
	CurrentZombieAlive--;

	if (CurrentZombieAlive <= 0)
	{
		NextPhase();
	}
}

void AGameLevel::PauseGame()
{
	GetWorld()->GetFirstPlayerController()->SetPause(true);
}

void AGameLevel::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &AGameLevel::PauseGame);
	}
}

