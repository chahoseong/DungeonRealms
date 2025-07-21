#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DungeonRealmsCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerInputComponentSetup, UInputComponent*)

UCLASS()
class DUNGEONREALMS_API ADungeonRealmsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADungeonRealmsCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	FOnPlayerInputComponentSetup OnPlayerInputComponentSetup;
};
