#include "CombatSystem/DungeonRealmsCombatSystemStatics.h"
#include "Physics/DungeonRealmsCollisionChannels.h"

bool UDungeonRealmsCombatSystemStatics::HasObstacleBetween(const AActor* SourceActor, const AActor* TargetActor)
{
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(SourceActor);
	CollisionQueryParams.AddIgnoredActor(TargetActor);
	CollisionQueryParams.bTraceComplex = false;

	FHitResult ObstacleHit;
	return SourceActor->GetWorld()->LineTraceSingleByChannel(
		ObstacleHit,
		SourceActor->GetActorLocation(),
		TargetActor->GetActorLocation(),
		DungeonRealms_TraceChannel_Obstacle,
		CollisionQueryParams
	);
}
