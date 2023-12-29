// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	MyChar = Cast<ACharacter>(GetOwningActor());
	if (!IsValid(MyChar))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("NoChar"));
		return;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Get Char"));
	}
	MyCharMovement = MyChar->GetCharacterMovement();
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (IsValid(MyChar))
	{
		Speed = MyCharMovement->Velocity.Size2D();

		if ((MyCharMovement->GetCurrentAcceleration() != FVector(0, 0, 0)) && (Speed > 3.0f))
			ShouldMove = true;
		else
			ShouldMove = false;
		
		IsFalling = MyCharMovement->IsFalling();
		GEngine->AddOnScreenDebugMessage(-1, 0.05f, FColor::Red, FString::Printf( TEXT("IsFalling = %d"), IsFalling ? 1 : 0) );
	}
}
