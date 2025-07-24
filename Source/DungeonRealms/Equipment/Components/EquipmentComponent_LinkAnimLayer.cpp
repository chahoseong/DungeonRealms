#include "Equipment/Components/EquipmentComponent_LinkAnimLayer.h"
#include "Equipment/DungeonRealmsEquipmentInstance.h"
#include "GameFramework/Character.h"

void UEquipmentComponent_LinkAnimLayer::OnEquipped(UDungeonRealmsEquipmentInstance* EquipmentInstance)
{
	if (!EquipmentInstance->IsLocallyControlled())
	{
		return;
	}

	ACharacter* OwningCharacter = Cast<ACharacter>(EquipmentInstance->GetPawn());
	if (!IsValid(OwningCharacter))
	{
		return;
	}

	OwningCharacter->GetMesh()->LinkAnimClassLayers(AnimLayerToLink);
}

void UEquipmentComponent_LinkAnimLayer::OnUnequipped(UDungeonRealmsEquipmentInstance* EquipmentInstance)
{
	if (!EquipmentInstance->IsLocallyControlled())
	{
		return;
	}

	ACharacter* OwningCharacter = Cast<ACharacter>(EquipmentInstance->GetPawn());
	if (!IsValid(OwningCharacter))
	{
		return;
	}

	OwningCharacter->GetMesh()->UnlinkAnimClassLayers(AnimLayerToLink);
}
