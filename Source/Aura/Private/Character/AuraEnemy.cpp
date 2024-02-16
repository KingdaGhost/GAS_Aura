// Copyright KingdaGhost Studios


#include "Character/AuraEnemy.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
}

void AAuraEnemy::HighlightActor()
{
	bHighlight = true;
}

void AAuraEnemy::UnHighlightActor()
{
	bHighlight = false;
}
