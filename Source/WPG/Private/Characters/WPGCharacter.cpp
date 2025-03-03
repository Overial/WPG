// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/WPGCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystemComponent.h"
#include "Abilities/WPGGameplayAbility.h"
#include "Abilities/PlayerAbilityInputID.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AWPGCharacter::AWPGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Spring Arm
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);

	// Camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	// Ability System
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

// Called when the game starts or when spawned
void AWPGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Add mapping context
	if (auto PlayerController = Cast<APlayerController>(Controller))
	{
		if (auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	InitAbilities(CharacterAbilities);
}

// Called every frame
void AWPGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind inputs
	if (auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWPGCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AWPGCharacter::Look);

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AWPGCharacter::HandleJumpPressed);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AWPGCharacter::HandleJumpReleased);

		// Showing Command Menu
		EnhancedInputComponent->BindAction(ShowCommandMenuAction, ETriggerEvent::Started, this, &AWPGCharacter::HandleShowCommandMenu);

		// Showing Pause Menu
		EnhancedInputComponent->BindAction(ShowPauseMenuAction, ETriggerEvent::Started, this, &AWPGCharacter::HandleShowPauseMenu);
	}
}

void AWPGCharacter::InitAbilities(TArray<TSubclassOf<UWPGGameplayAbility>> AbilitiesToAdd)
{
	if (IsValid(AbilitySystemComponent))
	{
		for (auto AbilityToAdd : AbilitiesToAdd)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(
				AbilityToAdd,
				AbilityToAdd.GetDefaultObject()->GetAbilityLevel(),
				static_cast<int32>(AbilityToAdd.GetDefaultObject()->GetPlayerAbilityInputID()),
				this
			));
		}
	}
}

void AWPGCharacter::Move(const FInputActionValue& Value)
{
	// Forward vector input
	AddMovementInput(FRotationMatrix(FRotator(0.0, GetControlRotation().Yaw, 0.0)).GetUnitAxis(EAxis::X), Value.Get<FVector2D>().Y);

	// Right vector input
	AddMovementInput(FRotationMatrix(FRotator(0.0, GetControlRotation().Yaw, 0.0)).GetUnitAxis(EAxis::Y), Value.Get<FVector2D>().X);
}

void AWPGCharacter::Look(const FInputActionValue& Value)
{
	// Pitch input
	AddControllerPitchInput(Value.Get<FVector2D>().Y);

	// Yaw input
	AddControllerYawInput(Value.Get<FVector2D>().X);
}

void AWPGCharacter::HandleJumpPressed()
{
	AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EPlayerAbilityInputID::Jump));
}

void AWPGCharacter::HandleJumpReleased()
{
	AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(EPlayerAbilityInputID::Jump));
}

void AWPGCharacter::HandleShowCommandMenu()
{
	AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EPlayerAbilityInputID::ToggleCommandMenu));
}

void AWPGCharacter::HandleShowPauseMenu()
{
	AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EPlayerAbilityInputID::TogglePauseMenu));
}
