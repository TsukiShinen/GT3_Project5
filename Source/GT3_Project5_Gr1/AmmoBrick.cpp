// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoBrick.h"


// Sets default values
AAmmoBrick::AAmmoBrick()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);
	VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	Pickable = CreateDefaultSubobject<UPickable>(TEXT("Pickable"));
	AddOwnedComponent(Pickable);
	Pickable->AttachTo(VisualMesh);

	Pickable->OnPickUp.AddDynamic(this, &AAmmoBrick::OnPickup);
}

// Called when the game starts or when spawned
void AAmmoBrick::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAmmoBrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAmmoBrick::OnPickup(AGT3_Project5_Gr1Character* Player)
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("TEST"));
	Player->GetInventory()->InventoryAmmo += AmmoAmount;
	if (Player->GetInventory()->InventoryAmmo > Player->GetInventory()->MaxInventoryAmmo)
	{
		Player->GetInventory()->InventoryAmmo = Player->GetInventory()->MaxInventoryAmmo;
	}
	Destroy();
}
