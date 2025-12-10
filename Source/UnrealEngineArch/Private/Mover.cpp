// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	if (Owner)
	{
		USceneComponent* ActorRoot = Owner->GetRootComponent();
		ActorRoot->SetMobility(EComponentMobility::Movable);
		WorldStartPosition = Owner->GetTransform().TransformPosition(LocalStartPosition);
		WorldEndPosition = Owner->GetTransform().TransformPosition(LocalEndPosition);

	}

}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (!GetOwner()) return;

	MoveObstacle(DeltaTime);
	
}

void UMover::MoveObstacle(float DeltaTime)
{
	FVector CurrentPosition = Owner->GetActorLocation();
	FVector TargetPosition = bIsMovingToEnd ? WorldStartPosition : WorldEndPosition;
	FVector Direction = (TargetPosition - CurrentPosition).GetSafeNormal();
	FVector NewPosition = CurrentPosition + MoveSpeed * DeltaTime * Direction;

	if (FVector::Dist(NewPosition, TargetPosition) < FVector::Dist(CurrentPosition, TargetPosition))
	{
		GetOwner()->SetActorLocation(NewPosition);
	}
	else
	{
		GetOwner()->SetActorLocation(TargetPosition);
		bIsMovingToEnd = !bIsMovingToEnd;
	}
}

