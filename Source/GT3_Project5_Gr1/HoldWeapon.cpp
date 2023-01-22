// Fill out your copyright notice in the Description page of Project Settings.


#include "HoldWeapon.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


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
	EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &UHoldWeapon::EndAim);
}

void UHoldWeapon::AttachWeapon(TSubclassOf<AWeapon> WeaponType, USkeletalMeshComponent* Mesh)
{
	if (!AnimInstance)
	{
		AnimInstance = Mesh->GetAnimInstance();
	}
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponType, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (Weapon)
	{
		Weapon->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Weapon_R"));
	}
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
	DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 2.0f, .0f, 10.0f);
	if (bIsActorHit && hit.GetActor())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, hit.GetActor()->GetName());
		Weapon->Shoot(hit.ImpactPoint, hit.GetActor());
	} else
	{
		Weapon->Shoot(end);
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

