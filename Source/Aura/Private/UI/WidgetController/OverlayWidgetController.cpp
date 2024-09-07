// Copyright KingdaGhost Studios


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "PlayerState/AuraPlayerState.h"

void UOverlayWidgetController::BroadcastInitialValue()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	AAuraPlayerState* AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);

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

	UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	if (AuraASC)
	{
		// if BindCallbacksToDependencies function gets called first then we will go to the else statement since the AuraASC will have not been initialised yet or the AddCharacterAbilities would have not been called yet
		// if AbilitiesGivenDelegate has already broadcasted from AuraASC then just call the callback itself 
		if (AuraASC->bStartupAbilitiesGiven)
		{
			OnInitializedStartupAbilities(AuraASC);
		}
		else
		{ // else we bind the callback to the OnInitializedStartupAbilities and will be called automatically when the Delegate has been broadcasted
			AuraASC->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnInitializedStartupAbilities);
		}

		AuraASC->EffectAssetTags.AddLambda(
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
	}
	
	if (AuraPlayerState)
	{
		AuraPlayerState->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);
	}
}

void UOverlayWidgetController::OnInitializedStartupAbilities(UAuraAbilitySystemComponent* AuraAbilitySystemComponent)
{
	//TODO: Get information about all given abilities, look up their Ability Info, and broadcast it to widgets
	if (!AuraAbilitySystemComponent->bStartupAbilitiesGiven) return;

	// The FForEachAbility is bounded here in this function by using the BindLambda function
	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this, AuraAbilitySystemComponent](const FGameplayAbilitySpec& AbilitySpec)
	{
		//TODO: Need a way to figure out the ability tag for a given ability spec.
		FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AuraAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
		Info.InputTag = AuraAbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
	});
	// This line is used for calling the ForEachAbility() to execute the Delegate.
	AuraAbilitySystemComponent->ForEachAbility(BroadcastDelegate);
}

void UOverlayWidgetController::OnXPChanged(int32 NewXP) const
{
	const AAuraPlayerState* AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	if (AuraPlayerState)
	{
		const ULevelUpInfo* LevelUpInfo = AuraPlayerState->LevelUpInfo;
		checkf(LevelUpInfo, TEXT("Unable to find LevelUpInfo. Please fill out AuraPlayerState Blueprint"));

		const int32 Level = LevelUpInfo->FindLevelForXP(NewXP);
		const int32 MaxLevel = LevelUpInfo->LevelUpInformation.Num();

		if (Level <= MaxLevel && Level > 0)
		{
			const int32 LevelUpRequirement = LevelUpInfo->LevelUpInformation[Level].LevelUpRequirement;
			const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInformation[Level - 1].LevelUpRequirement;

			const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
			const int32 XPForThisLevel = NewXP - PreviousLevelUpRequirement;

			const float XPBarPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelRequirement);

			OnXPPercentChangedDelegate.Broadcast(XPBarPercent);
		}
	}
}

