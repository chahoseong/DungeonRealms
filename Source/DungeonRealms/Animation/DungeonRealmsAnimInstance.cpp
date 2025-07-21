#include "Animation/DungeonRealmsAnimInstance.h"
#include "Character/DungeonRealmsCharacter.h"
#include "Character/DungeonRealmsCharacterMovementComponent.h"

UDungeonRealmsAnimInstance::UDungeonRealmsAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UDungeonRealmsAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UDungeonRealmsAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (const ADungeonRealmsCharacter* Character = Cast<ADungeonRealmsCharacter>(GetOwningActor()); IsValid(Character))
	{
		const UDungeonRealmsCharacterMovementComponent* CharacterMovement = CastChecked<UDungeonRealmsCharacterMovementComponent>(Character->GetCharacterMovement());
		const FDungeonRealmsCharacterGroundInfo& GroundInfo = CharacterMovement->GetGroundInfo();
		GroundDistance = GroundInfo.GroundDistance;
	}
}
