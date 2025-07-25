#pragma once

#include "CoreMinimal.h"
#include "DungeonRealmsAttackTracer.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "DungeonRealmsAttackTraceComponent.generated.h"

class UDungeonRealmsCombatSystemComponent;
class UAbilitySystemComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEONREALMS_API UDungeonRealmsAttackTraceComponent : public USceneComponent, public IDungeonRealmsAttackTracer
{
	GENERATED_BODY()

public:
	UDungeonRealmsAttackTraceComponent();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION(BlueprintCallable)
	void BeginTrace();

	UFUNCTION(BlueprintCallable)
	void PerformTrace(int32 Substeps, TArray<FHitResult>& OutHits);

	UFUNCTION(BlueprintCallable)
	void EndTrace();

	const FVector& GetExtent() const;

private:
	void RegisterToCombatSystem();
	void UnregisterFromCombatSystem();
	
	UDungeonRealmsCombatSystemComponent* GetCombatSystemComponent() const;
	
	FCollisionObjectQueryParams MakeObjectQueryParams() const;
	FCollisionQueryParams MakeTraceQueryParams() const;

	TArray<FHitResult> FilterNonBlockingHitsByObstacle(const TArray<FHitResult>& Hits) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Hitbox")
	FVector Extent = FVector::ZeroVector;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Hitbox")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Hitbox")
	bool bDebugDraw = false;
	
private:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag Tag;
	
	FTransform LastHitboxTransform;
};
