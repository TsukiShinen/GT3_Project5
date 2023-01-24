// Fill out your copyright notice in the Description page of Project Settings.


#include "HoldWeapon.h"
#include "EnhancedInputComponent.h"


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
	EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &UHoldWeapon::ShootAuto);
	EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &UHoldWeapon::EndAim);
}

void UHoldWeapon::SwitchWeapon(AWeapon* NewWeapon)
{
	if (Weapon)
	{
		Weapon->SetActorHiddenInGame(true);
	}
	Weapon = NewWeapon;
	Weapon->SetActorHiddenInGame(false);
}

// Called when the game starts
void UHoldWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void UHoldWeapon::Aim(const FInputActionValue& Value)
{
	bIsAiming = true;
	
	AimingStartEvent.Broadcast();

	if (!bIsShooting)
	{
		PlayAnimAim();
	}
}

void UHoldWeapon::Shoot(const FInputActionValue& Value)
{
	if (bIsShooting) return;
	if (!Weapon->HasAmmunitionLeft()) return;
	
	bIsShooting = true;

	PlayAnimShoot();

	FOnMontageBlendingOutStarted OnMontageBlendingOutStarted;
	OnMontageBlendingOutStarted.BindUFunction(this, "EndShoot");
	AnimInstance->Montage_SetBlendingOutDelegate(OnMontageBlendingOutStarted);

	FVector start = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
	FVector dir = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetActorForwardVector();
	FVector end  = start + (dir * 100000);
	FHitResult hit;
	
	bool bIsActorHit = GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Pawn, FCollisionQueryParams(), FCollisionResponseParams());
	if (bIsActorHit && hit.GetActor())
	{
		Weapon->Shoot(hit.ImpactPoint, hit.GetActor());
	} else
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

void UHoldWeapon::EndShoot()
{
	bIsShooting = false;
	
	if (bIsAiming)
	{
		AimingStartEvent.Broadcast();
		PlayAnimAim();
	}
}


// Called every frame
void UHoldWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

