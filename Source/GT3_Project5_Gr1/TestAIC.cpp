#include "TestAIC.h"


ATestAIC::ATestAIC()
{
}

void ATestAIC::BeginPlay()
{
	Super::BeginPlay();

	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void ATestAIC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveToActor();
}

EPathFollowingRequestResult::Type ATestAIC::MoveToActor()
{
	return Super::MoveToActor(Player);
}
