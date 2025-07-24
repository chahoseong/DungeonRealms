#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DungeonRealmsEquipmentComponent.generated.h"


class UDungeonRealmsEquipmentInstance;

UCLASS(Abstract, DefaultToInstanced, EditInlineNew)
class DUNGEONREALMS_API UDungeonRealmsEquipmentComponent : public UObject
{
	GENERATED_BODY()

public:
	virtual void OnEquipped(UDungeonRealmsEquipmentInstance* EquipmentInstance) { }
	virtual void OnUnequipped(UDungeonRealmsEquipmentInstance* EquipmentInstance) { }
};
