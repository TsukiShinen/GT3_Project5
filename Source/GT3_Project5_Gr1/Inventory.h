// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Weapon.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GT3_PROJECT5_GR1_API UInventory : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponChanged);

public:
	// Sets default values for this component's properties
	UInventory();
	
	void SetupPlayerInputComponent(class UEnhancedInputComponent* EnhancedInputComponent);
	void ChangeWeapon(const FInputActionValue& Value);

	void LoadWeapon(USkeletalMeshComponent* Mesh);

	AWeapon* GetCurrentWeapon() { return Weapons[CurrentWeaponIndex]; }
	UPROPERTY()
	FOnWeaponChanged OnWeaponChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ChangeWeaponAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon")
	TArray<TSubclassOf<AWeapon>> WeaponsType;
	
	UPROPERTY(BlueprintReadOnly, Category="Weapon")
	TArray<AWeapon*> Weapons;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon")
	int CurrentWeaponIndex = 0;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
