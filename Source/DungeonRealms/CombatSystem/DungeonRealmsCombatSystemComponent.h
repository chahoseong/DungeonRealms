#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DungeonRealmsCombatSystemComponent.generated.h"

struct FGameplayTag;
class IDungeonRealmsAttackTracer;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEONREALMS_API UDungeonRealmsCombatSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="DungeonRealms|CombatSystem")
	static UDungeonRealmsCombatSystemComponent* FindCombatSystemComponent(const AActor* Actor);
	
public:
	UDungeonRealmsCombatSystemComponent();

	void AddAttackTracer(FName SocketName, IDungeonRealmsAttackTracer* AttackTracer);
	void RemoveAttackTracer(FName SocketName);

	UFUNCTION(BlueprintCallable)
	void BeginAttackTrace(FName SocketName);

	UFUNCTION(BlueprintCallable)
	void PerformAttackTrace(FName SocketName, int32 Substeps);

	UFUNCTION(BlueprintCallable)
	void EndAttackTrace(FName SocketName);

private:
	void SetupAnimationSettingsOnDedicatedServer();
	void ResetAnimationSettingsOnDedicatedServer();
	
private:
	TMap<FName, TWeakInterfacePtr<IDungeonRealmsAttackTracer>> AttackTracers;
	
	EVisibilityBasedAnimTickOption CachedAnimTickOption;
	bool bCachedOnlyAllowAutonomousTickPose;
	bool bCachedEnableUpdateRateOptimizations;
};
