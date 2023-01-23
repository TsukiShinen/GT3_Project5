// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

#include "EnhancedInputComponent.h"
#include "InputTriggers.h"


// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInventory::LoadWeapon(USkeletalMeshComponent* Mesh)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	for (auto WeaponType : WeaponsType)
	{
		if (AWeapon* Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponType, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams))
		{
			Weapon->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Weapon_R"));
			Weapon->SetActorHiddenInGame(true);
			Weapons.Add(Weapon);
		}
	}
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UInventory::SetupPlayerInputComponent(UEnhancedInputComponent* EnhancedInputComponent)
{
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

