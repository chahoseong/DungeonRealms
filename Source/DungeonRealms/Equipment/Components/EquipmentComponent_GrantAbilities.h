#pragma once

#include "CoreMinimal.h"
#include "DungeonRealmsEquipmentComponent.h"
#include "GameplayTagContainer.h"
#include "EquipmentComponent_GrantAbilities.generated.h"

class UGameplayAbility;

USTRUCT()
struct FGameplayAbilityToGrant
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> Ability;

	UPROPERTY(EditDefaultsOnly)
	int32 Level;

	UPROPERTY(EditDefaultsOnly, meta=(Categories="Input"))
	FGameplayTag InputTag;
};

UCLASS(DisplayName="Grant Abilities")
class DUNGEONREALMS_API UEquipmentComponent_GrantAbilities : public UDungeonRealmsEquipmentComponent
{
	GENERATED_BODY()

public:
	virtual void OnEquipped(UDungeonRealmsEquipmentInstance* EquipmentInstance) override;
	virtual void OnUnequipped(UDungeonRealmsEquipmentInstance* EquipmentInstance) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<FGameplayAbilityToGrant> AbilitiesToGrant;
};
