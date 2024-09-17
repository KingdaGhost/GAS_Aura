// Copyright KingdaGhost Studios


#include "PlayerState/AuraPlayerState.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

AAuraPlayerState::AAuraPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AuraAbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AuraAttributeSet");
	
	NetUpdateFrequency = 100.f;
}

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAuraPlayerState, Level);
	DOREPLIFETIME(AAuraPlayerState, XP);
	DOREPLIFETIME(AAuraPlayerState, AttributePoints);
	DOREPLIFETIME(AAuraPlayerState, SpellPoints);
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraPlayerState::SetXP(int32 InXP)
{
	XP = InXP;
	// This broadcast will be received by OverlayWidgetController
	OnXPChangedDelegate.Broadcast(XP);
}

void AAuraPlayerState::SetLevel(int32 InLevel)
{
	Level = InLevel;
	// This broadcast will be received by OverlayWidgetController
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAuraPlayerState::SetAttributePoints(int32 InAttributePoints)
{
	AttributePoints = InAttributePoints;
	// This broadcast will be received by AttributeMenuWidgetController
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AAuraPlayerState::SetSpellPoints(int32 InSpellPoints)
{
	SpellPoints = InSpellPoints;
	// This broadcast will be received by AttributeMenuWidgetController
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}

void AAuraPlayerState::AddToAttributePoints(int32 InAttributePoints)
{
	AttributePoints += InAttributePoints;
	// This broadcast will be received by AttributeMenuWidgetController
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AAuraPlayerState::AddToSpellPoints(int32 InSpellPoints)
{
	SpellPoints += InSpellPoints;
	// This broadcast will be received by AttributeMenuWidgetController
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}

void AAuraPlayerState::AddToLevel(int32 InLevel)
{
	Level += InLevel;
	// This broadcast will be received by OverlayWidgetController
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAuraPlayerState::AddToXP(int32 InXP)
{
	XP += InXP;
	// This broadcast will be received by OverlayWidgetController
	OnXPChangedDelegate.Broadcast(XP);
}

void AAuraPlayerState::OnRep_Level(int32 OldLevel)
{
	// This broadcast will be received by OverlayWidgetController
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAuraPlayerState::OnRep_XP(int32 OldXP)
{
	// This broadcast will be received by OverlayWidgetController
	OnXPChangedDelegate.Broadcast(XP);
}

void AAuraPlayerState::OnRep_AttributePoints(int32 OldAttributePoints)
{
	// This broadcast will be received by AttributeMenuWidgetController
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AAuraPlayerState::OnRep_SpellPoints(int32 OldSpellPoints)
{
	// This broadcast will be received by AttributeMenuWidgetController
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}
