// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "GT3_Project5_Gr1Character.h"
#include "Components/ArrowComponent.h"


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


	Pickable = CreateDefaultSubobject<UPickable>(TEXT("Pickable"));
	AddOwnedComponent(Pickable);
	Pickable->AttachTo(VisualMesh);

	Pickable->OnPickUp.AddDynamic(this, &AWeapon::OnPickup);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	Ammunition = MaxAmmunition;
	Player = Cast<AGT3_Project5_Gr1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AWeapon::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Recoil = FMath::FInterpTo(Recoil, 0, DeltaSeconds, 10.0f);
	RecoilRecovery = FMath::FInterpTo(RecoilRecovery, -Recoil, DeltaSeconds, 20.0f);
	const float ApplyPitch = Recoil + RecoilRecovery;

	if (Player)
	{
		Player->AddControllerPitchInput(ApplyPitch);
	}
}

void AWeapon::Shoot(FVector End, AActor* Actor)
{
	if (Ammunition <= 0)
	{
		return;
	}
	Ammunition--;
	if (Actor)
	{
		UGameplayStatics::ApplyDamage(Actor, Damage,
									  UGameplayStatics::GetPlayerController(GetWorld(), 0), this, DamageType);
	}

	Recoil -= MaxRecoil;
}

void AWeapon::Reload(const int Amount)
{
	Ammunition = Amount;
}

void AWeapon::SetActivePickable(bool isActive)
{
	Pickable->SetActiveUpdate(isActive);
}

void AWeapon::OnPickup(AGT3_Project5_Gr1Character* newPlayer)
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("WEAPON"));
	newPlayer->GetInventory()->PickWeapon(this, newPlayer);
}
