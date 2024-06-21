// Copyright KingdaGhost Studios


#include "AuraGameplayTags.h"

#include "GameplayTagsManager.h"

// This is how we initialize a static variable
FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reducing damage taken, improves Block Chance"));
	
}
