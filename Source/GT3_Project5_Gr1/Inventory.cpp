// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

#include "EnhancedInputComponent.h"
#include "GT3_Project5_Gr1Character.h"
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
			Weapon->SetActivePickable(false);
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

void UInventory::PickWeapon(AWeapon* NewWeapon, AGT3_Project5_Gr1Character* NewPlayer)
{
	const auto OldWeapon = GetCurrentWeapon();
	OldWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	OldWeapon->SetActorLocationAndRotation(NewWeapon->GetActorLocation(), NewWeapon->GetActorRotation());

	NewWeapon->AttachToComponent(NewPlayer->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Weapon_R"));
	NewWeapon->SetActivePickable(false);
	
	Weapons[CurrentWeaponIndex] = NewWeapon;
	OnWeaponChanged.Broadcast();
	
	OldWeapon->SetActorHiddenInGame(false);
	OldWeapon->SetActivePickable(true);
}

void UInventory::SetupPlayerInputComponent(UEnhancedInputComponent* EnhancedInputComponent)
{
	EnhancedInputComponent->BindAction(ChangeWeaponAction, ETriggerEvent::Triggered, this, &UInventory::ChangeWeapon);
}

void UInventory::ChangeWeapon(const FInputActionValue& Value)
{
	const int IndexChange = Value.Get<float>();
	CurrentWeaponIndex += IndexChange;
	if (CurrentWeaponIndex < 0) CurrentWeaponIndex += Weapons.Num();
	if (CurrentWeaponIndex >= Weapons.Num()) CurrentWeaponIndex -= Weapons.Num();
	
	OnWeaponChanged.Broadcast();
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

