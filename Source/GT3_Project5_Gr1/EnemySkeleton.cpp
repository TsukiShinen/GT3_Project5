// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySkeleton.h"
#include "GT3_Project5_Gr1Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemySkeleton::AEnemySkeleton()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	/*
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SkeletalMesh->SetupAttachment(RootComponent);
	SkeletalMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));*/
}

// Called when the game starts or when spawned
void AEnemySkeleton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySkeleton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemySkeleton::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemySkeleton::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	Life -= Damage;
	if (Life <= 0)
	{
		Life = 0;
		K2_DestroyActor();
		AGT3_Project5_Gr1Character* Player = Cast<AGT3_Project5_Gr1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (Player)
		{
			Player->AddScore(10);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::FromInt(Player->GetScore()));
		}
	}
	
	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

