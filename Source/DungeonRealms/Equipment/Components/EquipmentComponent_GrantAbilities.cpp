#include "Equipment/Components/EquipmentComponent_GrantAbilities.h"
#include "Equipment/DungeonRealmsEquipmentInstance.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"

void UEquipmentComponent_GrantAbilities::OnEquipped(UDungeonRealmsEquipmentInstance* EquipmentInstance)
{
	if (!EquipmentInstance->HasAuthority())
	{
		return;
	}

	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(
		EquipmentInstance->GetPawn());
	if (!IsValid(AbilitySystemComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("[UEquipmentComponent_GrantAbilities] Invalid Ability System Component"))
		return;
	}

	for (const FGameplayAbilityToGrant& AbilityToGrant : AbilitiesToGrant)
	{
		if (!IsValid(AbilityToGrant.Ability))
		{
			continue;
		}
		FGameplayAbilitySpec AbilitySpec(AbilityToGrant.Ability, AbilityToGrant.Level);
		AbilitySpec.SourceObject = EquipmentInstance;
		if (AbilityToGrant.InputTag.IsValid())
		{
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilityToGrant.InputTag);
		}
		const FGameplayAbilitySpecHandle Handle = AbilitySystemComponent->GiveAbility(AbilitySpec);
		EquipmentInstance->AddGrantedAbilitySpecHandle(Handle);
	}
}

void UEquipmentComponent_GrantAbilities::OnUnequipped(UDungeonRealmsEquipmentInstance* EquipmentInstance)
{
	if (EquipmentInstance->HasAuthority())
	{
		EquipmentInstance->ClearGrantedAbilities();
	}
}
