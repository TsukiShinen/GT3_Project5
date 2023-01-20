// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "Weapon.h"
#include "GT3_Project5_Gr1Character.generated.h"


UCLASS(config=Game)
class AGT3_Project5_Gr1Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AimAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShootAction;


	UPROPERTY(EditAnywhere, Category = "Stats")
	float MaxWalkSpeed = 500.0f;
	
	UPROPERTY(EditAnywhere, Category = "Stats")
	float MaxWalkSpeedWhileAiming = 250.0f;
	
	UPROPERTY(VisibleAnywhere)
	AWeapon* Weapon;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> WeaponType;
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* ShootMontage;
	
	UPROPERTY(EditAnywhere)
	UAnimInstance* AnimInstance;
	
	UPROPERTY(VisibleAnywhere)
	bool bIsAiming;
	
	UPROPERTY(VisibleAnywhere)
	bool bIsShooting;
	
	UPROPERTY(VisibleAnywhere)
	int Score = 0;

public:
	AGT3_Project5_Gr1Character();

	UFUNCTION(BlueprintCallable)
	int GetScore() const { return Score; }
	void AddScore(int score) { Score += score; }

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	
	void Aim(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);
	void EndAim(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void EndShoot();
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

