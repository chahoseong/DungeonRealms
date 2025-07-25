#include "CombatSystem/DungeonRealmsAttackTraceComponent.h"
#include "DungeonRealmsCombatSystemComponent.h"
#include "CombatSystem/DungeonRealmsCombatSystemStatics.h"
#include "KismetTraceUtils.h"
#include "Kismet/KismetMathLibrary.h"

UDungeonRealmsAttackTraceComponent::UDungeonRealmsAttackTraceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDungeonRealmsAttackTraceComponent::BeginPlay()
{
	Super::BeginPlay();
	RegisterToCombatSystem();
}

void UDungeonRealmsAttackTraceComponent::RegisterToCombatSystem()
{
	UDungeonRealmsCombatSystemComponent* CombatSystemComponent = GetCombatSystemComponent();
	if (IsValid(CombatSystemComponent))
	{
		FName AttachedSocketName = GetOwner()->GetAttachParentSocketName();
		CombatSystemComponent->AddAttackTracer(AttachedSocketName, this);
	}
}

void UDungeonRealmsAttackTraceComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnregisterFromCombatSystem();
	Super::EndPlay(EndPlayReason);
}

void UDungeonRealmsAttackTraceComponent::UnregisterFromCombatSystem()
{
	UDungeonRealmsCombatSystemComponent* CombatSystemComponent = GetCombatSystemComponent();
	if (IsValid(CombatSystemComponent))
	{
		FName AttachedSocketName = GetOwner()->GetAttachParentSocketName();
		CombatSystemComponent->RemoveAttackTracer(AttachedSocketName);
	}
}

void UDungeonRealmsAttackTraceComponent::BeginTrace()
{
	LastHitboxTransform = GetComponentTransform();
}

void UDungeonRealmsAttackTraceComponent::PerformTrace(int32 Substeps, TArray<FHitResult>& OutHits)
{
	TArray<FHitResult> TotalHits;
	FCollisionObjectQueryParams ObjectQueryParams = MakeObjectQueryParams();
	FCollisionQueryParams TraceQueryParams = MakeTraceQueryParams();

	for (int32 i = 0; i < Substeps; ++i)
	{
		FTransform TraceStartTransform = UKismetMathLibrary::TLerp(
			LastHitboxTransform,
			GetComponentTransform(),
			static_cast<float>(i) / Substeps,
			ELerpInterpolationMode::DualQuatInterp
		);
		FTransform TraceEndTransform = UKismetMathLibrary::TLerp(
			LastHitboxTransform,
			GetComponentTransform(),
			static_cast<float>(i + 1) / Substeps,
			ELerpInterpolationMode::DualQuatInterp
		);
		FTransform TraceAverageTransform = UKismetMathLibrary::TLerp(
			TraceStartTransform,
			TraceEndTransform,
			0.5f,
			ELerpInterpolationMode::DualQuatInterp
		);

		TArray<FHitResult> SubHits;
		GetWorld()->SweepMultiByObjectType(
			SubHits,
			TraceStartTransform.GetLocation(),
			TraceEndTransform.GetLocation(),
			TraceAverageTransform.GetRotation(),
			ObjectQueryParams,
			FCollisionShape::MakeBox(Extent),
			TraceQueryParams
		);

		for (const FHitResult& HitResult : SubHits)
		{
			TraceQueryParams.AddIgnoredActor(HitResult.GetActor());
		}

		TotalHits.Append(SubHits);

		if (bDebugDraw)
		{
			DrawDebugSweptBox(
				GetWorld(),
				TraceStartTransform.GetLocation(),
				TraceEndTransform.GetLocation(),
				TraceAverageTransform.GetRotation().Rotator(),
				Extent,
				SubHits.Num() > 0 ? FColor::Red : FColor::Green,
				false,
				2.0f
			);
		}
	}

	OutHits = FilterNonBlockingHitsByObstacle(TotalHits);

	LastHitboxTransform = GetComponentTransform();
}

FCollisionObjectQueryParams UDungeonRealmsAttackTraceComponent::MakeObjectQueryParams() const
{
	FCollisionObjectQueryParams ObjectQueryParams;
	for (const TEnumAsByte<EObjectTypeQuery>& ObjectType : ObjectTypes)
	{
		ObjectQueryParams.AddObjectTypesToQuery(UEngineTypes::ConvertToCollisionChannel(ObjectType));
	}
	return ObjectQueryParams;
}

FCollisionQueryParams UDungeonRealmsAttackTraceComponent::MakeTraceQueryParams() const
{
	FCollisionQueryParams CollisionQueryParams(SCENE_QUERY_STAT(DungeonRealmsAttackTraceComponent_PerformTrace), false);
	const AActor* Actor = GetOwner();
	while (IsValid(Actor))
	{
		CollisionQueryParams.AddIgnoredActor(Actor);
		Actor = Actor->GetOwner();
	}
	return CollisionQueryParams;
}

TArray<FHitResult> UDungeonRealmsAttackTraceComponent::FilterNonBlockingHitsByObstacle(
	const TArray<FHitResult>& Hits) const
{
	TArray<FHitResult> Filtered;
	
	for (const FHitResult& HitResult : Hits)
	{
		if (!UDungeonRealmsCombatSystemStatics::HasObstacleBetween(GetOwner(), HitResult.GetActor()))
		{
			Filtered.Add(HitResult);
		}
	}

	return Filtered;
}

void UDungeonRealmsAttackTraceComponent::EndTrace()
{
	
}

const FVector& UDungeonRealmsAttackTraceComponent::GetExtent() const
{
	return Extent;
}

UDungeonRealmsCombatSystemComponent* UDungeonRealmsAttackTraceComponent::GetCombatSystemComponent() const
{
	AActor* Actor = GetOwner();
	
	while (IsValid(Actor))
	{
		UDungeonRealmsCombatSystemComponent* CombatSystemComponent = UDungeonRealmsCombatSystemComponent::FindCombatSystemComponent(Actor);
		if (IsValid(CombatSystemComponent))
		{
			return CombatSystemComponent;
		}
		Actor = Actor->GetOwner();
	}
	
	return nullptr;
}
