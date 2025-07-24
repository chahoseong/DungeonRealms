#pragma once

#include "CoreMinimal.h"
#include "DungeonRealmsEquipmentComponent.h"
#include "EquipmentComponent_AddInputMapping.generated.h"

class UInputMappingContext;

USTRUCT()
struct FInputMappingContextToApply
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly)
	int32 Priority;
};

UCLASS(DisplayName="Add InputMapping")
class DUNGEONREALMS_API UEquipmentComponent_AddInputMapping : public UDungeonRealmsEquipmentComponent
{
	GENERATED_BODY()

public:
	virtual void OnEquipped(UDungeonRealmsEquipmentInstance* EquipmentInstance) override;
	virtual void OnUnequipped(UDungeonRealmsEquipmentInstance* EquipmentInstance) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<FInputMappingContextToApply> InputMappingContextsToApply;
};
