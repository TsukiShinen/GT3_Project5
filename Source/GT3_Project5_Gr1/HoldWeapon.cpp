// Fill out your copyright notice in the Description page of Project Settings.


#include "HoldWeapon.h"

#include "GT3_Project5_Gr1Character.h"
#include "Components/ArrowComponent.h"
#include "Components/DecalComponent.h"
#include "Engine/DecalActor.h"


// Sets default values for this component's properties
UHoldWeapon::UHoldWeapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UHoldWeapon::SetupPlayerInputComponent(UEnhancedInputComponent* EnhancedInputComponent)
{
	EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &UHoldWeapon::Aim);
	EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &UHoldWeapon::Shoot);
	EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &UHoldWeapon::Reload);
	EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &UHoldWeapon::ShootAuto);
	EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &UHoldWeapon::EndAim);
}

void UHoldWeapon::SwitchWeapon(AWeapon* NewWeapon, AWeapon* SecondWeapon)
{
	const auto Player = Cast<AGT3_Project5_Gr1Character>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (SecondWeapon)
	{
		SecondWeapon->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		                                TEXT("SecondWeapon"));
	}
	Weapon = NewWeapon;
	Weapon->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,
	                          TEXT("Weapon_R"));
}

// Called when the game starts
void UHoldWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void UHoldWeapon::Aim(const FInputActionValue& Value)
{
	if (bIsShooting || bIsReloading)
	{
		return;
	}

	bIsAiming = true;

	AimingStartEvent.Broadcast();

	if (!bIsShooting)
	{
		PlayAnimAim();
	}
}

void UHoldWeapon::Shoot(const FInputActionValue& Value)
{
	if (bIsShooting || bIsReloading)
	{
		return;
	}
	if (!Weapon->HasAmmunitionLeft())
	{
		return;
	}

	bIsShooting = true;

	PlayAnimShoot();

	FOnMontageBlendingOutStarted OnMontageBlendingOutStarted;
	OnMontageBlendingOutStarted.BindUFunction(this, "EndShoot");
	AnimInstance->Montage_SetBlendingOutDelegate(OnMontageBlendingOutStarted);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ShootParticles,
	                                               Weapon->GetSpawnBullet()->GetComponentLocation(),
	                                               Weapon->GetSpawnBullet()->GetComponentRotation());

	FVector start = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
	FVector dir = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetActorForwardVector();
	FVector end = start + (dir * 100000);
	FHitResult hit;

	bool bIsActorHit = GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Pawn, FCollisionQueryParams(),
	                                                        FCollisionResponseParams());
	if (bIsActorHit && hit.GetActor())
	{
		Weapon->Shoot(hit.ImpactPoint, hit.GetActor());

		UNiagaraSystem* system = Cast<ACharacter>(hit.GetActor()) ? HitOnEnemyParticles : HitParticles;
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), system, hit.ImpactPoint, (start - end).Rotation());
		ADecalActor* decal = GetWorld()->SpawnActor<ADecalActor>(hit.Location, FRotator());
		if (decal)
		{
			decal->SetDecalMaterial(ActionDecalToSpawn);
			decal->SetLifeSpan(2.0f);
			decal->SetActorScale3D(FVector(0.2f, 0.2f, 0.2f));
			decal->GetDecal()->DecalSize = FVector(32.0f, 64.0f, 64.0f);
		}
	}
	else
	{
		Weapon->Shoot(end);
	}
}

void UHoldWeapon::ShootAuto(const FInputActionValue& Value)
{
	if (Weapon->IsAuto())
	{
		Shoot(Value);
	}
}

void UHoldWeapon::EndAim(const FInputActionValue& Value)
{
	bIsAiming = false;

	if (!bIsShooting)
	{
		StopAnimAimAndShoot();
	}
	AimingEndEvent.Broadcast();
}

void UHoldWeapon::Reload(const FInputActionValue& Value)
{
	if (bIsShooting || bIsReloading)
	{
		return;
	}

	bIsReloading = true;

	//Weapon
	PlayAnimReload();
	FOnMontageBlendingOutStarted OnMontageBlendingOutStarted;
	OnMontageBlendingOutStarted.BindUFunction(this, "EndReload");
	AnimInstance->Montage_SetBlendingOutDelegate(OnMontageBlendingOutStarted);
}

void UHoldWeapon::EndShoot()
{
	bIsShooting = false;

	if (bIsAiming)
	{
		AimingStartEvent.Broadcast();
		PlayAnimAim();
	}
}

void UHoldWeapon::EndReload()
{
	auto Player = Cast<AGT3_Project5_Gr1Character>(GetWorld()->GetFirstPlayerController()->GetPawn());

	auto inventoryAmmoAmount = Player->GetInventory()->InventoryAmmo;
	auto weaponMagSize = Weapon->GetMaxAmmunition();
	auto weaponMagSizeToReload = Weapon->GetMaxAmmunition() - Weapon->GetAmmunition();

	if (inventoryAmmoAmount - weaponMagSizeToReload >= 0)
	{
		Weapon->Reload(weaponMagSize);
		Player->GetInventory()->InventoryAmmo -= weaponMagSizeToReload;
	}
	else
	{
		Weapon->Reload(inventoryAmmoAmount + Weapon->GetAmmunition());
		Player->GetInventory()->InventoryAmmo = 0;
	}

	bIsReloading = false;
}


// Called every frame
void UHoldWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
