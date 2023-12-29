// Fill out your copyright notice in the Description page of Project Settings.


#include "CCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedPlayerInput.h"
#include "CPlayerController.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACCharacter::ACCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	GetMesh()->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));
}

// Called when the game starts or when spawned
void ACCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* UEIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (IsValid(UEIC))
	{
		UEIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
		UEIC->BindAction(IA_Jump, ETriggerEvent::Canceled, this, &ACCharacter::StopJumping);

		UEIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ACCharacter::Move);
		UEIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ACCharacter::Look);
	}
}

void ACCharacter::Move(const FInputActionValue& Value)
{
	FVector2D Dir = Value.Get<FVector2D>();	
	FRotator CameraRotation = GetControlRotation();
	FRotator DirectionRotation = FRotator(0, CameraRotation.Yaw, 0);

	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(DirectionRotation);
	FVector RightVector = UKismetMathLibrary::GetRightVector(DirectionRotation);

	AddMovementInput(ForwardVector, Dir.Y);
	AddMovementInput(RightVector, Dir.X);
}

void ACCharacter::Look(const FInputActionValue& Value)
{
	FVector2D Rot = Value.Get<FVector2D>();
	AddControllerPitchInput(Rot.Y);
	AddControllerYawInput(Rot.X);
}

