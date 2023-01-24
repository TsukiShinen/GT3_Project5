// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	VisualMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(VisualMesh);

	VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	VisualMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	SpawnBullet = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnBullet"));
	SpawnBullet->SetupAttachment(VisualMesh);

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	Ammunition = MaxAmmunition;
}

void AWeapon::Shoot(FVector End, AActor* Actor)
{
	if (Ammunition <= 0) return;
	Ammunition--;
	DrawDebugLine(GetWorld(), SpawnBullet->GetComponentLocation(), End, FColor::Red, false, 2.0f, .0f, 10.0f);
	if (Actor)
	{
		UGameplayStatics::ApplyDamage(Actor, Damage,
			UGameplayStatics::GetPlayerController(GetWorld(), 0), this, DamageType); 
	}
}

void AWeapon::Reload(const int Amount)
{
	Ammunition = Amount;
}

