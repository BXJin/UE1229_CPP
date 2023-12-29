// Fill out your copyright notice in the Description page of Project Settings.

#include "CPlayerController.h"
#include "EnhancedInputSubsystems.h"

void ACPlayerController::BeginPlay()
{
	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IsValid(SubSystem) && DefaultIMC)
	{
		SubSystem->AddMappingContext(DefaultIMC,0);
	}
}
