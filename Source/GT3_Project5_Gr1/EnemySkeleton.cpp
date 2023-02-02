// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySkeleton.h"
#include "GT3_Project5_Gr1Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemySkeleton::AEnemySkeleton()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemySkeleton::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AEnemySkeleton::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AEnemySkeleton::BeginPlay()
{
	Super::BeginPlay();
	AnimInstance = GetMesh()->GetAnimInstance();
	UAudioComponent* AudioComponent = UGameplayStatics::SpawnSound2D(this, EnemyCue);
}

// Called every frame
void AEnemySkeleton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemySkeleton::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AEnemySkeleton::TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator,
                                 AActor* DamageCauser)
{
	Life -= Damage;
	if (Life <= 0)
	{
		Life = 0;
		IsAlive = false;
		GetCharacterMovement()->Deactivate();
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			OnDeath.Broadcast();
			K2_DestroyActor();
		}, 1, false);

		if (AGT3_Project5_Gr1Character* Player = Cast<AGT3_Project5_Gr1Character>(
			UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
		{
			Player->AddScore(10);
		}
	}

	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

void AEnemySkeleton::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto Player = Cast<AGT3_Project5_Gr1Character>(OtherActor))
	{
		IsAttacking = true;

		PlayAttackAnim();
	}
}

void AEnemySkeleton::PlayAttackAnim()
{ 
	AnimInstance->Montage_Play(AM_Skeleton_Attack);
}

void AEnemySkeleton::StopAttackAnim()
{
	AnimInstance->Montage_Stop(0.5f, AM_Skeleton_Attack);
}

void AEnemySkeleton::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (auto Player = Cast<AGT3_Project5_Gr1Character>(OtherActor))
	{
		IsAttacking = false;
		StopAttackAnim();
	}
}


