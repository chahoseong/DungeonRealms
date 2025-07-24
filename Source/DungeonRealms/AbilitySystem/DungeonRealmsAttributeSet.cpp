#include "AbilitySystem/DungeonRealmsAttributeSet.h"
#include "Net/UnrealNetwork.h"

UDungeonRealmsAttributeSet::UDungeonRealmsAttributeSet()
{
}

void UDungeonRealmsAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UDungeonRealmsAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDungeonRealmsAttributeSet, Mana, COND_None, REPNOTIFY_Always);
}

void UDungeonRealmsAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDungeonRealmsAttributeSet, Health, OldHealth);
}

void UDungeonRealmsAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDungeonRealmsAttributeSet, Mana, OldMana);
}
