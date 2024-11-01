// Copyright KingdaGhost Studios


#include "AbilitySystem/Abilities/AuraFireBolt.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	const int32 ScaledDamage = FMath::RoundToInt(Damage.GetValueAtLevel(Level));
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
			Level, ManaCost, Cooldown, ScaledDamage);
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
		Level, ManaCost, Cooldown, FMath::Min(Level, NumProjectiles), ScaledDamage);
	
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	const int32 ScaledDamage = FMath::RoundToInt(Damage.GetValueAtLevel(Level));
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
		Level, ManaCost, Cooldown, FMath::Min(Level, NumProjectiles), ScaledDamage);
}