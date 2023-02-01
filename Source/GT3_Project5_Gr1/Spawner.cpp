// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"


// Sets default values
ASpawner::ASpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Triggerbox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	Triggerbox->SetupAttachment(RootComponent);
	Triggerbox->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(Triggerbox);
	VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	Triggerbox->OnComponentBeginOverlap.AddDynamic(this, &ASpawner::OnOverlapBegin);
	Triggerbox->OnComponentEndOverlap.AddDynamic(this, &ASpawner::OnOverlapEnd);
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

void ASpawner::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                              class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult& SweepResult)
{
	if (OtherActor == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		Spawning = true;
	}
}

void ASpawner::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                            int32 OtherBodyIndex)
{
	if (OtherActor == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		Spawning = false;
	}
}

void ASpawner::Spawn()
{
	if (Enemy && Spawning && bIsActive)
	{
		AEnemySkeleton* EnemySpawned = GetWorld()->SpawnActor<AEnemySkeleton>(Enemy, GetActorLocation(), FRotator());
		OnSpawn.Broadcast(EnemySpawned);
	}
}
