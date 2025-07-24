#include "Equipment/Weapon/UDungeonRealmsGameplayAbility_MeleeWeapon.h"
#include "AbilitySystemComponent.h"

UUDungeonRealmsGameplayAbility_MeleeWeapon::UUDungeonRealmsGameplayAbility_MeleeWeapon(
	const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
}

void UUDungeonRealmsGameplayAbility_MeleeWeapon::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	bWasComboCommitted = false;

	if (HasAuthority(&CurrentActivationInfo))
	{
		
	}
}

void UUDungeonRealmsGameplayAbility_MeleeWeapon::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UUDungeonRealmsGameplayAbility_MeleeWeapon::CommitCombo()
{
	if (bWasComboCommitted)
	{
		return;
	}

	const UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	if (const FGameplayAbilitySpec* NextAttackSpec = AbilitySystemComponent->FindAbilitySpecFromClass(NextAttackClass))
	{
		if (HasAuthority(&CurrentActivationInfo))
		{
			AdvanceCombo(NextAttackSpec->Handle);
		}
		else
		{
			ServerCommitCombo(NextAttackSpec->Handle);
			AdvanceCombo(NextAttackSpec->Handle);
		}
	}
}

void UUDungeonRealmsGameplayAbility_MeleeWeapon::ServerCommitCombo_Implementation(
	FGameplayAbilitySpecHandle NextAttackSpecHandle)
{
	if (IsComboWindowOpen() && IsCorrectPrediction(NextAttackSpecHandle))
	{
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
	}
	else
	{
		UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
		AbilitySystemComponent->CancelAbilityHandle(NextAttackSpecHandle);
	}
}

bool UUDungeonRealmsGameplayAbility_MeleeWeapon::IsCorrectPrediction(
	FGameplayAbilitySpecHandle PredictedAbilitySpecHandle) const
{
	const UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	if (const FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromHandle(PredictedAbilitySpecHandle))
	{
 		return NextAttackClass == AbilitySpec->Ability->GetClass();
	}
	return false;
}

void UUDungeonRealmsGameplayAbility_MeleeWeapon::AdvanceCombo(FGameplayAbilitySpecHandle AbilitySpecHandle)
{
	UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponentFromActorInfo();
	AbilitySystem->TryActivateAbility(AbilitySpecHandle);
	bWasComboCommitted = true;
}

void UUDungeonRealmsGameplayAbility_MeleeWeapon::OpenComboWindow()
{
	bComboWindowOpen = true;
}

void UUDungeonRealmsGameplayAbility_MeleeWeapon::CloseComboWindow()
{
	bComboWindowOpen = false;
	ComboWindowCloseTime = GetWorld()->GetTimeSeconds();
}

bool UUDungeonRealmsGameplayAbility_MeleeWeapon::IsComboWindowOpen() const
{
	if (HasAuthority(&CurrentActivationInfo))
	{
		const float ComboCommitLatency = GetWorld()->GetTimeSeconds() - ComboWindowCloseTime;
		return bComboWindowOpen || ComboCommitLatency <= AllowedComboWindowTolerance;
	}
	else
	{
		return bComboWindowOpen;
	}
}



