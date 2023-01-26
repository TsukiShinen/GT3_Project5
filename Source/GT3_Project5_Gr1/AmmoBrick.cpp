// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoBrick.h"

// Sets default values
AAmmoBrick::AAmmoBrick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Triggerbox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	Triggerbox->SetupAttachment(RootComponent);
	Triggerbox->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(Triggerbox);
	VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	Triggerbox->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBrick::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AAmmoBrick::BeginPlay()
{
	Super::BeginPlay();
	
	if (VFX) 
	{
		UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(VFX, RootComponent, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);
	}
}

// Called every frame
void AAmmoBrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * 10.0f;       //Scale our height by a factor of 20
	float DeltaRotation = DeltaTime * 80.0f;    //Rotate by 20 degrees per second
	NewRotation.Yaw += DeltaRotation;
	SetActorLocationAndRotation(NewLocation, NewRotation);
}

void AAmmoBrick::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AMMO PICKUP"));
		auto Player = Cast<AGT3_Project5_Gr1Character>(GetWorld()->GetFirstPlayerController()->GetPawn());
		Player->GetInventory().
	}
}

