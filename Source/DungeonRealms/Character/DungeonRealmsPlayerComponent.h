#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DungeonRealmsPlayerComponent.generated.h"

class UInputMappingContext;
class UDungeonRealmsInputConfig;

struct FInputActionValue;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONREALMS_API UDungeonRealmsPlayerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDungeonRealmsPlayerComponent();

protected:
	virtual void OnRegister() override;
	virtual void BeginPlay() override;

private:
	void InitializePlayerInput(UInputComponent* PlayerInputComponent);
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

protected:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputMappingContext> DefaultInputMapping;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UDungeonRealmsInputConfig> InputConfig;	
};
