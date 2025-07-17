#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DungeonRealmsInputConfig.h"
#include "DungeonRealmsInputComponent.generated.h"

struct FGameplayTag;

UCLASS()
class DUNGEONREALMS_API UDungeonRealmsInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template <class UserClass, typename FuncType>
	void BindNativeAction(
		const UDungeonRealmsInputConfig* InputConfig,
		const FGameplayTag& InputTag,
		ETriggerEvent TriggerEvent,
		UserClass* Object,
		FuncType Func,
		bool bLogIfNotFound
	);
};

template <class UserClass, typename FuncType>
void UDungeonRealmsInputComponent::BindNativeAction(const UDungeonRealmsInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, bool bLogIfNotFound)
{
	check(InputConfig);

	if (const UInputAction* InputAction = InputConfig->FindNativeInputActionForTag(InputTag, bLogIfNotFound))
	{
		BindAction(InputAction, TriggerEvent, Object, Func);
	}
}
