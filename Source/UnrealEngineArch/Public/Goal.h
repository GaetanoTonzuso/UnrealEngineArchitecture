// Fill out your copyright notice in the Description page of Project Settings.

//TODO: Notify the goal that has been hit (Physics Hit)
//TODO: By the ship actor
//TODO: Stop timer?? We need a timer object
//TODO: Activate Celebration

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Goal.generated.h"

UCLASS()
class UNREALENGINEARCH_API AGoal : public AActor
{
	GENERATED_BODY() 
	
public:	
	// Sets default values for this actor's properties
	AGoal();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyHit(class UPrimitiveComponent* MyComp, 
		AActor* Other, 
		class UPrimitiveComponent* OtherComp, 
		bool bSelfMoved, FVector HitLocation, 
		FVector HitNormal, 
		FVector NormalImpulse, 
		const FHitResult& Hit) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CheckLandPlayer();


private:	
	
	bool bHasReachedGoal;
};
