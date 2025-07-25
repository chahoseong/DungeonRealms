#include "AttackTraceComponentVisualizer.h"
#include "DungeonRealms/CombatSystem/DungeonRealmsAttackTraceComponent.h"

void FAttackTraceComponentVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View,
	FPrimitiveDrawInterface* PDI)
{
	const UDungeonRealmsAttackTraceComponent* AttackTraceComponent = Cast<const UDungeonRealmsAttackTraceComponent>(Component);
	if (!IsValid(AttackTraceComponent))
	{
		return;
	}

	FTransform Transform = AttackTraceComponent->GetComponentTransform();
	DrawWireBox(
		PDI,
		Transform.ToMatrixNoScale(),
		FBox::BuildAABB(Transform.GetLocation(), AttackTraceComponent->GetExtent()),
		FColor::Red,
		SDPG_World
	);
}
