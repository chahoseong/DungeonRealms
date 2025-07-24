#include "Equipment/Components/EquipmentComponent_AddInputMapping.h"
#include "Equipment/DungeonRealmsEquipmentInstance.h"
#include "EnhancedInputSubsystems.h"

void UEquipmentComponent_AddInputMapping::OnEquipped(UDungeonRealmsEquipmentInstance* EquipmentInstance)
{
	if (!EquipmentInstance->IsLocallyControlled())
	{
		return;
	}
	
	APawn* OwningPawn = EquipmentInstance->GetPawn();
	if (!IsValid(OwningPawn))
	{
		return;
	}

	APlayerController* PlayerController = OwningPawn->GetController<APlayerController>();
	if (!IsValid(PlayerController))
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (IsValid(Subsystem))
	{
		for (const FInputMappingContextToApply& ContextToApply : InputMappingContextsToApply)
		{
			Subsystem->AddMappingContext(ContextToApply.InputMappingContext, ContextToApply.Priority);
		}
	}
}

void UEquipmentComponent_AddInputMapping::OnUnequipped(UDungeonRealmsEquipmentInstance* EquipmentInstance)
{
	if (!EquipmentInstance->IsLocallyControlled())
	{
		return;
	}
	
	APawn* OwningPawn = EquipmentInstance->GetPawn();
	if (!IsValid(OwningPawn))
	{
		return;
	}

	APlayerController* PlayerController = OwningPawn->GetController<APlayerController>();
	if (!IsValid(PlayerController))
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (IsValid(Subsystem))
	{
		for (const FInputMappingContextToApply& ContextToApply : InputMappingContextsToApply)
		{
			Subsystem->RemoveMappingContext(ContextToApply.InputMappingContext);
		}
	}
}
