// Copyright KingdaGhost Studios


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "PlayerState/AuraPlayerState.h"

void UOverlayWidgetController::BroadcastInitialValue()
{
	OnHealthChanged.Broadcast(GetAuraAS()->GetHealth());
	OnMaxHealthChanged.Broadcast(GetAuraAS()->GetMaxHealth());
	OnManaChanged.Broadcast(GetAuraAS()->GetMana());
	OnMaxManaChanged.Broadcast(GetAuraAS()->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	#define BIND_CALLBACK( AttributeName ) AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->Get##AttributeName##Attribute()).AddLambda( \
		[this](const FOnAttributeChangeData& Data) \
		{\
			On##AttributeName##Changed.Broadcast(Data.NewValue); \
		});

		BIND_CALLBACK(Health);
		BIND_CALLBACK(MaxHealth);
		BIND_CALLBACK(Mana);
		BIND_CALLBACK(MaxMana);
	#undef BIND_CALLBACK
	
	if (GetAuraASC())
	{
		// if BindCallbacksToDependencies function gets called first then we will go to the else statement since the AuraASC will have not been initialised yet or the AddCharacterAbilities would have not been called yet
		// if AbilitiesGivenDelegate has already broadcasted from AuraASC then just call the callback itself 
		if (GetAuraASC()->bStartupAbilitiesGiven)
		{
			BroadcastAbilityInfo();
		}
		else
		{ // else we bind the callback to the OnInitializedStartupAbilities and will be called automatically when the Delegate has been broadcasted
			GetAuraASC()->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::BroadcastAbilityInfo);
		}

		GetAuraASC()->EffectAssetTags.AddLambda(
		// The square brackets is used for capturing the object that which we can use its member function. In this case, we want to use GetDataTableRowByTag which is a member function of this class so we use the 'this' keyword
		[this](const FGameplayTagContainer& AssetTags)
			{
				for (const FGameplayTag& Tag : AssetTags)
				{
					// For example, say that Tag = Message.HealthPotion
					// "Message.HealthPotion".MatchesTag("Message") will return True, "Message".MatchesTag("Message.HealthPotion") will return False
					FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
					if (Tag.MatchesTag(MessageTag))
					{
						FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
						MessageWidgetRowDelegate.Broadcast(*Row);
					}				
				}
			}
		);
		// Binding to the AbilityEquipped which gets called when we select an ability and assign it to an offensive or passive slot
		GetAuraASC()->AbilityEquipped.AddUObject(this, &UOverlayWidgetController::OnAbilityEquipped);
	}
	
	if (GetAuraPS())
	{
		GetAuraPS()->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);
		GetAuraPS()->OnLevelChangedDelegate.AddLambda(
			[this](int32 NewLevel)
			{
				OnPlayerLevelChangedDelegate.Broadcast(NewLevel);
			}
			);
	}
}

void UOverlayWidgetController::OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status,
	const FGameplayTag& SlotTag, const FGameplayTag& PreviousSlot) const
{
	const FAuraGameplayTags& AuraGameplayTags = FAuraGameplayTags::Get();
	
	// Clearing out the old slot
	// Using the PreviousSlot which means the PreviousInputTag, e.g, firebolt in input LMB now changed to RMB then the PreviousSlot will be LMB, will set everything to default values
	// Even the icons and such will be set to null. So make sure to handle on the blueprint side to not set a blank white image on the icon.
	FAuraAbilityInfo LastSlotInfo;
	LastSlotInfo.StatusTag = AuraGameplayTags.Abilities_Status_Unlocked;
	LastSlotInfo.InputTag = PreviousSlot;
	LastSlotInfo.AbilityTag = AuraGameplayTags.Abilities_None;
	// Broadcast empty info if PreviousSlot is a valid Slot. Only if equipping an already equipped spell
	AbilityInfoDelegate.Broadcast(LastSlotInfo);

	// Filling out the new slot
	FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
	Info.StatusTag = Status;
	Info.InputTag = SlotTag;
	AbilityInfoDelegate.Broadcast(Info);
}

void UOverlayWidgetController::OnXPChanged(int32 NewXP)
{
	// CastChecked will be converted to static cast in the build game. So no problems with performance
	if (GetAuraPS())
	{
		const ULevelUpInfo* LevelUpInfo = GetAuraPS()->LevelUpInfo;
		checkf(LevelUpInfo, TEXT("Unable to find LevelUpInfo. Please fill out AuraPlayerState Blueprint"));

		const int32 Level = LevelUpInfo->FindLevelForXP(NewXP);
		const int32 MaxLevel = LevelUpInfo->LevelUpInformation.Num();

		if (Level <= MaxLevel && Level > 0)
		{
			const int32 LevelUpRequirement = LevelUpInfo->LevelUpInformation[Level].LevelUpRequirement;
			const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInformation[Level - 1].LevelUpRequirement;

			// suppose we are in level 2, LevelUpRequirement will be 900 and PreviousLevelUpRequirement will be 300, so Delta will be 900 - 300 = 600
			const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
			// XP for this level will be the current XP that we have which will be between 300 and 899. Lets take 500 as current XP and the PreviousLevelUpRequirement will be 300 which will be calculated to 500 - 300=200
			const int32 XPForThisLevel = NewXP - PreviousLevelUpRequirement;
			// So the XPBarPercent will be XPForThisLevel divided by DeltaRequirement, which will be calculated as 200/600 = 0.333..
			const float XPBarPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelRequirement);

			OnXPPercentChangedDelegate.Broadcast(XPBarPercent);
		}
	}
}

