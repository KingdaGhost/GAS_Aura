// Copyright KingdaGhost Studios


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

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
}

void UAttributeMenuWidgetController::BroadcastInitialValue()
{
	// The DataAsset
	check(AttributeInfo);

	for (FAuraAttributeInfo& AttrInfo : AttributeInfo.Get()->AttributeInformation)
	{
		BroadcastAttributeInfo(AttrInfo.AttributeTag);
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Info.AttributeGetter.GetNumericValue(CastChecked<UAuraAttributeSet>(AttributeSet));
	AttributeInfoDelegate.Broadcast(Info);
}
