#include "Character/DungeonRealmsCharacter.h"
#include "DungeonRealmsCharacterMovementComponent.h"
#include "AI/Navigation/NavigationTypes.h"
#include "CombatSystem/DungeonRealmsCombatSystemComponent.h"
#include "Components/CapsuleComponent.h"

ADungeonRealmsCharacter::ADungeonRealmsCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UDungeonRealmsCharacterMovementComponent>(CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	
	GetCapsuleComponent()->InitCapsuleSize(40.0f, 90.0f);
	// CapsuleComponent->SetCollisionProfileName();
	
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	// MeshComponent->SetCollisionProfileName()

	UDungeonRealmsCharacterMovementComponent* DungeonRealmsCharacterMovement = CastChecked<UDungeonRealmsCharacterMovementComponent>(GetCharacterMovement());
	DungeonRealmsCharacterMovement->GravityScale = 1.0f;
	DungeonRealmsCharacterMovement->MaxAcceleration = 2400.0f;
	DungeonRealmsCharacterMovement->BrakingFrictionFactor = 1.0f;
	DungeonRealmsCharacterMovement->BrakingFriction = 6.0f;
	DungeonRealmsCharacterMovement->GroundFriction = 8.0;
	DungeonRealmsCharacterMovement->BrakingDecelerationWalking = 1400.0f;
	DungeonRealmsCharacterMovement->bUseControllerDesiredRotation = false;
	DungeonRealmsCharacterMovement->bOrientRotationToMovement = false;
	DungeonRealmsCharacterMovement->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	DungeonRealmsCharacterMovement->bAllowPhysicsRotationDuringAnimRootMotion = false;
	DungeonRealmsCharacterMovement->GetNavAgentPropertiesRef().bCanCrouch = true;
	DungeonRealmsCharacterMovement->bCanWalkOffLedgesWhenCrouching = true;
	DungeonRealmsCharacterMovement->SetCrouchedHalfHeight(65.0f);

	CombatSystemComponent = CreateDefaultSubobject<UDungeonRealmsCombatSystemComponent>(TEXT("CombatSystemComponent"));
}

UAbilitySystemComponent* ADungeonRealmsCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ADungeonRealmsCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

UDungeonRealmsCombatSystemComponent* ADungeonRealmsCharacter::GetCombatSystemComponent() const
{
	return CombatSystemComponent;
}
