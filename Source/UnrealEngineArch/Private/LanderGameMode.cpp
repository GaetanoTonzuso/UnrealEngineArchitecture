// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "LanderGameMode.h"

ALanderGameMode::ALanderGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	CountdownTimer = 30.f;
}

void ALanderGameMode::BeginPlay()
{
	Super::BeginPlay();

	Timer = CountdownTimer;
}

void ALanderGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Current Timer: %f"),Timer));
	}

	if (Timer > 0)
	{
		Timer -= DeltaTime;
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Timer is 0 or less"));
		FName LevelName = *UGameplayStatics::GetCurrentLevelName(GetWorld(),true);
		UGameplayStatics::OpenLevel(GetWorld(),LevelName,true);
	}

}

