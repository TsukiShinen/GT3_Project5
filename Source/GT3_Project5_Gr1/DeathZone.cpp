// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathZone.h"
#include "GT3_Project5_Gr1Character.h"

// Sets default values
ADeathZone::ADeathZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADeathZone::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ADeathZone::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADeathZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADeathZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto Player = Cast<AGT3_Project5_Gr1Character>(OtherActor))
	{
		Player->SetHP(0);
	}
}