#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CombatSystem/DungeonRealmsCombatSystemInterface.h"
#include "DungeonRealmsCharacter.generated.h"

class UAttributeSet;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPossessed, AController*)

UCLASS()
class DUNGEONREALMS_API ADungeonRealmsCharacter : public ACharacter, public IAbilitySystemInterface, public IDungeonRealmsCombatSystemInterface
{
	GENERATED_BODY()

public:
	ADungeonRealmsCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	template <typename T>
	T* GetAbilitySystemComponent() const
	{
		return Cast<T>(GetAbilitySystemComponent());
	}

	UAttributeSet* GetAttributeSet() const;

	template <typename T>
	T* GetAttributeSet() const
	{
		return Cast<T>(GetAttributeSet());
	}

	virtual UDungeonRealmsCombatSystemComponent* GetCombatSystemComponent() const override;

protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY()
	TObjectPtr<UDungeonRealmsCombatSystemComponent> CombatSystemComponent;
};
