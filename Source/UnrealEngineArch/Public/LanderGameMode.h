// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LanderGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALENGINEARCH_API ALanderGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	ALanderGameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BLueprintReadOnly, Category = "Gameplay")
	float CountdownTimer;


protected:

private:
	float Timer;
	
};
