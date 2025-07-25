#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DungeonRealmsAttackTracer.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UDungeonRealmsAttackTracer : public UInterface
{
	GENERATED_BODY()
};

struct FGameplayTag;

class DUNGEONREALMS_API IDungeonRealmsAttackTracer
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void BeginTrace() { }
	virtual void PerformTrace(int32 Substeps, TArray<FHitResult>& OutHits) { }
	virtual void EndTrace() { }
};
