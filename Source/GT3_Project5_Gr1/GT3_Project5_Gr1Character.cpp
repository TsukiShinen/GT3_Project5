// Copyright Epic Games, Inc. All Rights Reserved.

#include "GT3_Project5_Gr1Character.h"

#include <Windows.Data.Text.h>

#include "EnhancedInputComponent.h"
#include "GameLevel.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"


//////////////////////////////////////////////////////////////////////////
// AGT3_Project5_Gr1Character

AGT3_Project5_Gr1Character::AGT3_Project5_Gr1Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	GetCharacterMovement()->bUseControllerDesiredRotation = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = CameraArmLenght; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	FollowCamera->SetRelativeLocation(FollowCameraOffset);

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	HoldWeapon = CreateDefaultSubobject<UHoldWeapon>(TEXT("Hold Weapon"));
	AddOwnedComponent(HoldWeapon);
	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
	AddOwnedComponent(Inventory);
}

void AGT3_Project5_Gr1Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	Inventory->LoadWeapon(GetMesh());

	Inventory->OnWeaponChanged.AddDynamic(this, &AGT3_Project5_Gr1Character::OnWeaponChanged);

	HoldWeapon->SetAnimInstance(GetMesh()->GetAnimInstance());
	HoldWeapon->SwitchWeapon(Inventory->GetCurrentWeapon());

	HoldWeapon->AimingStartEvent.AddLambda([&]()-> void
	{
		FollowCamera->SetRelativeLocation(FollowCameraOffsetAiming);
		CameraBoom->TargetArmLength = CameraArmLenghtAiming;
		GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeedWhileAiming;
	});
	HoldWeapon->OnEndAim().AddLambda([&]()-> void
	{
		FollowCamera->SetRelativeLocation(FollowCameraOffset);
		CameraBoom->TargetArmLength = CameraArmLenght;
		GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	});
	HoldWeapon->OnSniping().AddLambda([&]()-> void
	{
		FollowCamera->SetRelativeLocation(FollowCameraOffsetSnipe);
		CameraBoom->TargetArmLength = CameraArmLenghtSnipe;
		GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeedWhileAiming;
	});
}

//////////////////////////////////////////////////////////////////////////
// Input

void AGT3_Project5_Gr1Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
		                                   &AGT3_Project5_Gr1Character::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this,
		                                   &AGT3_Project5_Gr1Character::Look);

		Inventory->SetupPlayerInputComponent(EnhancedInputComponent);
		HoldWeapon->SetupPlayerInputComponent(EnhancedInputComponent);
	}
}

void AGT3_Project5_Gr1Character::DealDamage(float damage)
{
	HP -= damage;
	if (HP < 0)
	{
		HP = 0;
	}
}

void AGT3_Project5_Gr1Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AGT3_Project5_Gr1Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
