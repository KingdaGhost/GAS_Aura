// Copyright KingdaGhost Studios


#include "AbilitySystem/Abilities/AuraSummonAbility.h"

#include "Kismet/KismetSystemLibrary.h"

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
		const FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);
		SpawnLocation.Add(ChosenSpawnLocation);
		DrawDebugSphere(GetWorld(), ChosenSpawnLocation, 18.f, 12, FColor::Cyan, false, 3.f);
		UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Location, Location + Direction * MaxSpawnDistance, 4.f, FLinearColor::Green, 3);
		
		DrawDebugSphere(GetWorld(), Location + Direction * MinSpawnDistance, 10.f, 12, FColor::Red, false, 3.f);
		DrawDebugSphere(GetWorld(), Location + Direction * MaxSpawnDistance, 10.f, 12, FColor::Red, false, 3.f);
	}
	
	return SpawnLocation;
}
