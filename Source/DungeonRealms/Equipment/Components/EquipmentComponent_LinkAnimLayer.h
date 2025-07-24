#pragma once

#include "CoreMinimal.h"
#include "DungeonRealmsEquipmentComponent.h"
#include "EquipmentComponent_LinkAnimLayer.generated.h"

UCLASS(DisplayName="Link AnimLayer")
class DUNGEONREALMS_API UEquipmentComponent_LinkAnimLayer : public UDungeonRealmsEquipmentComponent
{
	GENERATED_BODY()

public:
	virtual void OnEquipped(UDungeonRealmsEquipmentInstance* EquipmentInstance) override;
	virtual void OnUnequipped(UDungeonRealmsEquipmentInstance* EquipmentInstance) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAnimInstance> AnimLayerToLink;
};
