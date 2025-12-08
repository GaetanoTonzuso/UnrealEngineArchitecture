// Fill out your copyright notice in the Description page of Project Settings.

#include "Goal.h"

#include "Ship.h"

// Sets default values
AGoal::AGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGoal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGoal::NotifyHit(class UPrimitiveComponent* MyComp, 
	AActor* Other, 
	class UPrimitiveComponent* OtherComp, 
	bool bSelfMoved, 
	FVector HitLocation, 
	FVector HitNormal, 
	FVector NormalImpulse, 
	const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if (Other && Other != this && Other->IsA(AShip::StaticClass()))
	{
		if (!bHasReachedGoal)
		{
			bHasReachedGoal = true;
			UE_LOG(LogTemp, Warning, TEXT("Goaaaaal!"));
		}
	}

}

