// Copyright KingdaGhost Studios


#include "AbilitySystem/Abilities/AuraSummonAbility.h"


TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnSpread / NumMinions;

	// We are rotating about the Z axis. This is rotating to the right of the character by half of the SpawnSpread
	// const FVector RightOfSpread = Forward.RotateAngleAxis(SpawnSpread/2.f, FVector::UpVector);

	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread/2.f, FVector::UpVector);
	TArray<FVector> SpawnLocation;
	//This for loop is to make an even spread for the Number of Minions to be spawned
	for (int32 i = 0; i < NumMinions; i++)
	{
		// The spread is going from left to right since the DeltaSpread is +ve
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);

		// This trace is done for the purpose of always spawning correctly in the case of a staircase or a ramp or a hill
		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, ChosenSpawnLocation + FVector(0.f, 0.f, 400.f), ChosenSpawnLocation + FVector(0.f, 0.f, -400.f), ECC_Visibility);
		if (Hit.bBlockingHit)
		{
			ChosenSpawnLocation = Hit.ImpactPoint;
		}
		SpawnLocation.Add(ChosenSpawnLocation);
	}
	
	return SpawnLocation;
}
