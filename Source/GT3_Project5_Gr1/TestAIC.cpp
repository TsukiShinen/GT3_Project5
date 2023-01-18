#include "TestAIC.h"


ATestAIC::ATestAIC()
{
}

void ATestAIC::BeginPlay()
{
	MoveToActor();
}

EPathFollowingRequestResult::Type ATestAIC::MoveToActor()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	//AActor* Actor = Cast<AActor>(Character); Note a moi même : Ne fonctionne pas -_-

	return Super::MoveToActor((AActor*)Player);
}
