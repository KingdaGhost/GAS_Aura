// Copyright KingdaGhost Studios


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "PlayerState/AuraPlayerState.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	check(AttributeInfo);

	for (FAuraAttributeInfo& AttrInfo : AttributeInfo.Get()->AttributeInformation)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttrInfo.AttributeGetter).AddLambda(
			[this, AttrInfo](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(AttrInfo.AttributeTag);
			}
		);
	}

	AAuraPlayerState* AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	if (AuraPlayerState)
	{
		AuraPlayerState->OnAttributePointsChangedDelegate.AddUObject(this, &UAttributeMenuWidgetController::OnAttributePointsChanged);
		AuraPlayerState->OnSpellPointsChangedDelegate.AddUObject(this, &UAttributeMenuWidgetController::OnSpellPointsChanged);
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValue()
{
	// The DataAsset
	check(AttributeInfo);

	for (FAuraAttributeInfo& AttrInfo : AttributeInfo.Get()->AttributeInformation)
	{
		BroadcastAttributeInfo(AttrInfo.AttributeTag);
	}
	if (const AAuraPlayerState* AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState))
	{
		AttributePointsChangedDelegate.Broadcast(AuraPlayerState->GetAttributePoints());
		SpellPointsChangedDelegate.Broadcast(AuraPlayerState->GetSpellPoints());
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Info.AttributeGetter.GetNumericValue(CastChecked<UAuraAttributeSet>(AttributeSet));
	AttributeInfoDelegate.Broadcast(Info);
}

void UAttributeMenuWidgetController::OnAttributePointsChanged(int32 NewAttributePoints)
{
	AttributePointsChangedDelegate.Broadcast(NewAttributePoints);
}

void UAttributeMenuWidgetController::OnSpellPointsChanged(int32 NewSpellPoints)
{
	SpellPointsChangedDelegate.Broadcast(NewSpellPoints);
}

