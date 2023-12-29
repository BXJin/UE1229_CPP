// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

class ACharacter;
class UCharacterMovementComponent;

UCLASS()
class L1229UE5_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadonly, EditAnywhere)
	ACharacter* MyChar;

	UPROPERTY(BlueprintReadonly, EditAnywhere)
	UCharacterMovementComponent* MyCharMovement;

	UPROPERTY(BlueprintReadonly, EditAnywhere)
	float Speed;

	UPROPERTY(BlueprintReadonly, EditAnywhere)
	bool IsFalling;

	UPROPERTY(BlueprintReadonly, EditAnywhere)
	bool ShouldMove;
};
