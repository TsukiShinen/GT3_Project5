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

	UFUNCTION(BlueprintCallable)
	AWeapon* GetCurrentWeapon() { return Weapons[CurrentWeaponIndex]; }
	UFUNCTION(BlueprintCallable)
	AWeapon* GetSecondWeapon() { return Weapons[CurrentWeaponIndex == 0 ? 1 : 0]; }
	UPROPERTY()
	FOnWeaponChanged OnWeaponChanged;

	int MaxInventoryAmmo = 200;
	int InventoryAmmo = MaxInventoryAmmo / 2;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ChangeWeaponAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon")
	TArray<TSubclassOf<AWeapon>> WeaponsType;
	
	UPROPERTY(BlueprintReadWrite, Category="Weapon")
	TArray<AWeapon*> Weapons;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon")
	int CurrentWeaponIndex = 0;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PickWeapon(AWeapon* NewWeapon, AGT3_Project5_Gr1Character* NewPlayer);
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetInventoryAmmo() { return InventoryAmmo; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetInventoryMaxAmmo() { return MaxInventoryAmmo; }
};
