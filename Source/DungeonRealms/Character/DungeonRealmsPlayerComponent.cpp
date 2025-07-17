#include "Character/DungeonRealmsPlayerComponent.h"
#include "Character/DungeonRealmsCharacter.h"
#include "DungeonRealmsGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "Input/DungeonRealmsInputComponent.h"
#include "Input/DungeonRealmsInputConfig.h"

UDungeonRealmsPlayerComponent::UDungeonRealmsPlayerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDungeonRealmsPlayerComponent::OnRegister()
{
	Super::OnRegister();

	ADungeonRealmsCharacter* OwningCharacter = GetOwner<ADungeonRealmsCharacter>();
	if (IsValid(OwningCharacter))
	{
		OwningCharacter->OnPlayerInputComponentSetup.AddUObject(this, &ThisClass::InitializePlayerInput);
	}
}

void UDungeonRealmsPlayerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDungeonRealmsPlayerComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	const APawn* OwningPawn = GetOwner<APawn>();
	if (!IsValid(OwningPawn))
	{
		return;
	}

	const APlayerController* OwningPlayerController = OwningPawn->GetController<APlayerController>();
	check(OwningPlayerController);

	const ULocalPlayer* LocalPlayer = OwningPlayerController->GetLocalPlayer();
	check(LocalPlayer);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->AddMappingContext(DefaultInputMapping, 0);
	
	UDungeonRealmsInputComponent* DungeonRealmsInputComponent = Cast<UDungeonRealmsInputComponent>(PlayerInputComponent);
	check(DungeonRealmsInputComponent);
	
	DungeonRealmsInputComponent->BindNativeAction(InputConfig, DungeonRealmsGameplayTags::Input_Action_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move, false);
	DungeonRealmsInputComponent->BindNativeAction(InputConfig, DungeonRealmsGameplayTags::Input_Action_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look, false);
}

void UDungeonRealmsPlayerComponent::Input_Move(const FInputActionValue& InputActionValue)
{
	APawn* OwningPawn = GetOwner<APawn>();
	AController* OwningController = IsValid(OwningPawn) ? OwningPawn->GetController() : nullptr;

	if (IsValid(OwningController))
	{
		const FVector2D MovementInput = InputActionValue.Get<FVector2D>();
		const FRotator TargetRotation(0.0f, OwningController->GetControlRotation().Yaw, 0.0f);

		if (MovementInput.X != 0.0f)
		{
			const FVector RightDirection = TargetRotation.RotateVector(FVector::RightVector);
			OwningPawn->AddMovementInput(RightDirection, MovementInput.X);
		}

		if (MovementInput.Y != 0.0f)
		{
			const FVector ForwardDirection = TargetRotation.RotateVector(FVector::ForwardVector);
			OwningPawn->AddMovementInput(ForwardDirection, MovementInput.Y);
		}
	}
}

void UDungeonRealmsPlayerComponent::Input_Look(const FInputActionValue& InputActionValue)
{
	APawn* OwningPawn = GetOwner<APawn>();

	if (IsValid(OwningPawn))
	{
		const FVector2D LookInput = InputActionValue.Get<FVector2D>();
		if (LookInput.X != 0.0f)
		{
			OwningPawn->AddControllerYawInput(LookInput.X);
		}
		if (LookInput.Y != 0.0f)
		{
			OwningPawn->AddControllerPitchInput(LookInput.Y);
		}
	}
}
