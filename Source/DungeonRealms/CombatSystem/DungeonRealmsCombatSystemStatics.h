#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DungeonRealmsCombatSystemStatics.generated.h"

UCLASS()
class DUNGEONREALMS_API UDungeonRealmsCombatSystemStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static bool HasObstacleBetween(const AActor* SourceActor, const AActor* TargetActor);
};
