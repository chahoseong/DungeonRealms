#include "CombatSystem/DungeonRealmsCombatSystemComponent.h"
#include "CombatSystem/DungeonRealmsCombatSystemInterface.h"
#include "CombatSystem/DungeonRealmsAttackTracer.h"
#include "GameFramework/Character.h"

UDungeonRealmsCombatSystemComponent* UDungeonRealmsCombatSystemComponent::FindCombatSystemComponent(const AActor* Actor)
{
	if (IsValid(Actor))
	{
		if (const IDungeonRealmsCombatSystemInterface* CombatSystemInterface = Cast<const IDungeonRealmsCombatSystemInterface>(Actor))
		{
			return CombatSystemInterface->GetCombatSystemComponent();	
		}
		
		UDungeonRealmsCombatSystemComponent* CombatSystemComponent = Actor->FindComponentByClass<UDungeonRealmsCombatSystemComponent>();
		if (IsValid(CombatSystemComponent))
		{
			return CombatSystemComponent;
		}
	}
	return nullptr;
}

UDungeonRealmsCombatSystemComponent::UDungeonRealmsCombatSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDungeonRealmsCombatSystemComponent::AddAttackTracer(FName SocketName, IDungeonRealmsAttackTracer* AttackTracer)
{
	if (AttackTracer)
	{
		AttackTracers.Add(SocketName, AttackTracer);
	}
}

void UDungeonRealmsCombatSystemComponent::RemoveAttackTracer(FName SocketName)
{
	AttackTracers.Remove(SocketName);
}

void UDungeonRealmsCombatSystemComponent::BeginAttackTrace(FName SocketName)
{
#if WITH_SERVER_CODE
	SetupAnimationSettingsOnDedicatedServer();
#endif
	
	if (const auto Tracer = AttackTracers.FindRef(SocketName); Tracer.IsValid())
	{
		Tracer->BeginTrace();
	}
}

void UDungeonRealmsCombatSystemComponent::SetupAnimationSettingsOnDedicatedServer()
{
	ACharacter* OwningCharacter = GetOwner<ACharacter>();
	if (IsValid(OwningCharacter) && IsRunningDedicatedServer())
	{
		CachedAnimTickOption = OwningCharacter->GetMesh()->VisibilityBasedAnimTickOption;
		OwningCharacter->GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;

		bCachedOnlyAllowAutonomousTickPose = OwningCharacter->GetMesh()->bOnlyAllowAutonomousTickPose;
		OwningCharacter->GetMesh()->bOnlyAllowAutonomousTickPose = false;

		bCachedEnableUpdateRateOptimizations = OwningCharacter->GetMesh()->bEnableUpdateRateOptimizations;
		OwningCharacter->GetMesh()->bEnableUpdateRateOptimizations = false;
	}
}

void UDungeonRealmsCombatSystemComponent::PerformAttackTrace(FName SocketName, int32 Substeps)
{
	if (const auto Tracer = AttackTracers.FindRef(SocketName); Tracer.IsValid())
	{
		TArray<FHitResult> Hits;
		Tracer->PerformTrace(Substeps, Hits);
	}
}

void UDungeonRealmsCombatSystemComponent::EndAttackTrace(FName SocketName)
{
	if (const auto Tracer = AttackTracers.FindRef(SocketName); Tracer.IsValid())
	{
		Tracer->EndTrace();
	}
	
#if WITH_SERVER_CODE
	ResetAnimationSettingsOnDedicatedServer();
#endif
}

void UDungeonRealmsCombatSystemComponent::ResetAnimationSettingsOnDedicatedServer()
{
	ACharacter* OwningCharacter = GetOwner<ACharacter>();
	if (IsValid(OwningCharacter) && IsRunningDedicatedServer())
	{
		OwningCharacter->GetMesh()->VisibilityBasedAnimTickOption = CachedAnimTickOption;
		OwningCharacter->GetMesh()->bOnlyAllowAutonomousTickPose = bCachedOnlyAllowAutonomousTickPose;
		OwningCharacter->GetMesh()->bEnableUpdateRateOptimizations = bCachedEnableUpdateRateOptimizations;
	}
}
