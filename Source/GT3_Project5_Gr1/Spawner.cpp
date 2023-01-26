// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"


// Sets default values
ASpawner::ASpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	VisualMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	Delegate.BindUFunction(this, "Spawn");

	GetWorld()->GetTimerManager().SetTimer(Handle, Delegate, SpawnCooldown, true);
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawner::Spawn()
{
	if (Enemy)
	{
		GetWorld()->SpawnActor<AEnemySkeleton>(Enemy, GetActorLocation(), FRotator());
	}
}

