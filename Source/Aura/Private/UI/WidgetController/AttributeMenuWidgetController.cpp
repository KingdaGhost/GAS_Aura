// Copyright KingdaGhost Studios


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
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
	
	if (GetAuraPS())
	{
		GetAuraPS()->OnAttributePointsChangedDelegate.AddUObject(this, &UAttributeMenuWidgetController::OnAttributePointsChanged);
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
	if (GetAuraPS())
	{
		AttributePointsChangedDelegate.Broadcast(GetAuraPS()->GetAttributePoints());
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Info.AttributeGetter.GetNumericValue(CastChecked<UAuraAttributeSet>(AttributeSet));
	AttributeInfoDelegate.Broadcast(Info);
}

void UAttributeMenuWidgetController::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	// Just need to call UpgradeAttribute() from AuraASC from here
	GetAuraASC()->UpgradeAttribute(AttributeTag);
}

void UAttributeMenuWidgetController::OnAttributePointsChanged(int32 NewAttributePoints) const
{
	AttributePointsChangedDelegate.Broadcast(NewAttributePoints);
}

