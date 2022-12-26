// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"

#include "SnakeElementBase.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100;
	MovementSpeed = 10;
	LastMovementDirection = EMovementDirection::UP;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed); 
	AddSnakeElement(1);
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ASnakeBase::AddSnakeElement(int ElementsNum)
{
	for (int i = 0; i < ElementsNum; i++)
	{
		FVector NewLocation(SnakeElements.Num()*ElementSize, 0, 0);
		FTransform NewTransform(NewLocation);
		ASnakeElementBase* SnakeElement = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
		SnakeElement->Snake = this;
		int32 ElemIndex = SnakeElements.Add(SnakeElement);

		if(ElemIndex == 0)
		{
			SnakeElement->SetFirstElementType();
		}
	}
}

void ASnakeBase::Move()
{
	FVector MovementVector(ForceInitToZero);
	float Speed = ElementSize;

	switch (LastMovementDirection)
	{
		case EMovementDirection::UP:
			MovementVector.X += Speed;
			break;
		case EMovementDirection::DOWN:
			MovementVector.X -= Speed;
			break;
		case EMovementDirection::LEFT:
			MovementVector.Y += Speed;
			break;
		case EMovementDirection::RIGHT:
			MovementVector.Y -= Speed;
			break;
	}

	SnakeElements[0]->ToggleCollision();
	
	for (int i = SnakeElements.Num() - 1; i > 0; i--)
	{
		auto CurrentElement = SnakeElements[i];
		auto PreviousElement =  SnakeElements[i - 1] ;

		FVector PrevLocation = PreviousElement->GetActorLocation();
		CurrentElement->SetActorLocation(PrevLocation);
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCollision();
}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* OverlappedBlock, AActor* Other)
{
	if(IsValid(OverlappedBlock))
	{
		int Index;
		SnakeElements.Find(OverlappedBlock, Index);
		bool BlockIsFirst = Index == 0;

		IInteractable* Interactable = Cast<IInteractable>(Other);
		
		if(Interactable)
		{
			Interactable->Interact(this, BlockIsFirst);
		}
	}
}

