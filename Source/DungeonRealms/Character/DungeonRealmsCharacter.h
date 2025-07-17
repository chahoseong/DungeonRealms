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
	ADungeonRealmsCharacter();

	FOnPlayerInputComponentSetup OnPlayerInputComponentSetup;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
