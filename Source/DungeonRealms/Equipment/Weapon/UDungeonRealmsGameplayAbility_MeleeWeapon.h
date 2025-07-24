#pragma once

#include "CoreMinimal.h"
#include "Equipment/DungeonRealmsGameplayAbility_FromEquipment.h"
#include "UDungeonRealmsGameplayAbility_MeleeWeapon.generated.h"

UCLASS()
class DUNGEONREALMS_API UUDungeonRealmsGameplayAbility_MeleeWeapon : public UDungeonRealmsGameplayAbility_FromEquipment
{
	GENERATED_BODY()

public:
	UUDungeonRealmsGameplayAbility_MeleeWeapon(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION(BlueprintCallable)
	void CommitCombo();

	UFUNCTION(BlueprintCallable)
	void OpenComboWindow();
	
	UFUNCTION(BlueprintCallable)
	void CloseComboWindow();

	UFUNCTION(BlueprintPure)
	bool IsComboWindowOpen() const;

private:
	UFUNCTION(Server, Reliable)
	void ServerCommitCombo(FGameplayAbilitySpecHandle NextAttackSpecHandle);

	bool IsCorrectPrediction(FGameplayAbilitySpecHandle PredictedAbilitySpecHandle) const;
	void AdvanceCombo(FGameplayAbilitySpecHandle AbilitySpecHandle);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> NextAttackClass;

private:
	float ComboWindowCloseTime = 0.0f;
	float AllowedComboWindowTolerance = 0.15f;
	bool bComboWindowOpen = false;
	bool bWasComboCommitted = false;
};
