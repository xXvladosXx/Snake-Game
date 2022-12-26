 // Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnBase.h"

#include "SnakeBase.h"
#include "Camera/CameraComponent.h"

 // Sets default values
APlayerPawnBase::APlayerPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	RootComponent = PawnCamera;
}

// Called when the game starts or when spawned
void APlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorRotation(FRotator(-90.0f, 0.0f, 0.0f));
	CreateSnakeActor();
}

// Called every frame
void APlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Vertical", this, &APlayerPawnBase::HandlePlayerVerticalInput);
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerPawnBase::HandlePlayerHorizontalInput);
}

 void APlayerPawnBase::CreateSnakeActor()
 {
	Snake = GetWorld()->SpawnActor<ASnakeBase>(SnakeClass, FTransform());
 }

 void APlayerPawnBase::HandlePlayerVerticalInput(float Value)
 {
	if(IsValid(Snake))
	{
		if(Value > 0 && Snake->LastMovementDirection != EMovementDirection::DOWN)
		{
			Snake->LastMovementDirection = EMovementDirection::UP;
		}else if(Value < 0 && Snake->LastMovementDirection != EMovementDirection::UP)
		{
			Snake->LastMovementDirection = EMovementDirection::DOWN;
		}
	}
 }

 void APlayerPawnBase::HandlePlayerHorizontalInput(float Value)
 {
	if(IsValid(Snake))
	{
		if(Value > 0 && Snake->LastMovementDirection != EMovementDirection::LEFT)
		{
			Snake->LastMovementDirection = EMovementDirection::RIGHT;
		}else if(Value < 0 && Snake->LastMovementDirection != EMovementDirection::RIGHT)
		{
			Snake->LastMovementDirection = EMovementDirection::LEFT;
		}
	}
 }

