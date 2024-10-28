// Copyright KingdaGhost Studios


#include "AbilitySystem/Abilities/AuraFireBolt.h"
#include "AuraGameplayTags.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	const int32 Damage = FMath::RoundToInt(GetDamageByDamageType(Level, FAuraGameplayTags::Get().Damage_Fire));
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BOLT</>\n\n"
			// Details
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			// Description
			"<Default>Launches a bolt of fire, "
			"exploding on impact and dealing </><Damage>%d </><Default>"
			"fire damage with a chance to burn</>"),
			// Values
			Level, ManaCost, Cooldown, Damage);
	}
	return FString::Printf(TEXT(
		// Title
		"<Title>FIRE BOLT</>\n\n"
		// Details
		"<Small>Level: </><Level>%d</>\n"
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
		// Description
		"<Default>Launches %d bolts of fire, "
		"exploding on impact and dealing </><Damage>%d </><Default>"
		"fire damage with a chance to burn</>"),
		// Values
		Level, ManaCost, Cooldown, FMath::Min(Level, NumProjectiles), Damage);
	
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	const int32 Damage = FMath::RoundToInt(GetDamageByDamageType(Level, FAuraGameplayTags::Get().Damage_Fire));
	return FString::Printf(TEXT(
		// Title
		"<Title>NEXT LEVEL</>\n\n"
		//Details
		"<Small>Level: </><Level>%d</>\n"
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
		// Description
		"<Default>Launches %d bolts of fire, exploding on impact and dealing "
		"</><Damage>%d </><Default>fire damage with a chance to burn</>"),
		// Values
		Level, ManaCost, Cooldown, FMath::Min(Level, NumProjectiles), Damage);
}