#pragma once

#include "CoreMinimal.h"
#include "DungeonRealmsCharacter.h"
#include "DungeonRealmsPlayerCharacter.generated.h"

class UDungeonRealmsEquipmentDefinition;
class UDungeonRealmsEquipmentManagerComponent;
struct FInputActionValue;

UCLASS()
class DUNGEONREALMS_API ADungeonRealmsPlayerCharacter : public ADungeonRealmsCharacter
{
	GENERATED_BODY()

public:
	ADungeonRealmsPlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~Begin APawn interface
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	//~End APawn interface
	
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

protected:
	virtual void BeginPlay() override;

private:
	void InitializeAbilitySystem();

protected:
	UPROPERTY()
	TObjectPtr<UDungeonRealmsEquipmentManagerComponent> EquipmentManagerComponent;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UDungeonRealmsEquipmentDefinition>> StartupEquipmentClasses;
};
