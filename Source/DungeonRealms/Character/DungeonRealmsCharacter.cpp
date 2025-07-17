#include "Character/DungeonRealmsCharacter.h"

ADungeonRealmsCharacter::ADungeonRealmsCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ADungeonRealmsCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADungeonRealmsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADungeonRealmsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	OnPlayerInputComponentSetup.Broadcast(PlayerInputComponent);
}

