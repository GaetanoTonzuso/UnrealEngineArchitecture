// Fill out your copyright notice in the Description page of Project Settings.

#include "Ship.h"
#include "EnhancedInputComponent.h"
#include <EnhancedInputSubsystems.h>
#include "Kismet/GameplayStatics.h"


AShip::AShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	SetRootComponent(ShipMesh);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(ShipMesh);
	CameraBoom->TargetArmLength = 1000.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

void AShip::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			SubSystem->ClearAllMappings();
			SubSystem->AddMappingContext(ShipMappingContext,0);
		}
	}
}


void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(PropelInput, ETriggerEvent::Triggered, this, &AShip::PropelUp);
		EnhancedInputComponent->BindAction(RotateInput, ETriggerEvent::Triggered, this, &AShip::RotateShip);
	}
}


void AShip::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	HandleShipLand();
}

void AShip::PropelUp(const FInputActionValue& Value)
{
	bool CurrentValue = Value.Get<bool>();
	if (CurrentValue)
	{
		const FVector WorldImpulseVector = FVector(0.f,0.f,1.f) * ImpulseStrenght;
		const FVector LocalImpulseVector = GetActorRotation().RotateVector(WorldImpulseVector);
		ShipMesh->AddImpulse(LocalImpulseVector, NAME_None, true);
	}
}

void AShip::RotateShip(const FInputActionValue& Value)
{
	float CurrentValue = Value.Get<float>();
	const FVector TorqueVector = FVector(1.f, 0 , 0) * CurrentValue * TorqueStrenght;

	ShipMesh->AddTorqueInRadians(TorqueVector, NAME_None, true);

}

bool AShip::IsLandedSafely()
{
	FRotator CurrentRotation = GetActorRotation();
	float AccettableRollTollerance = 40.f;
	
	return FMath::Abs(CurrentRotation.Roll) <= AccettableRollTollerance;
}

void AShip::HandleShipLand()
{
	if (!IsLandedSafely())
	{
		UE_LOG(LogTemp, Warning, TEXT("Crashed!"));
		FName CurrentLevelName = *UGameplayStatics::GetCurrentLevelName(GetWorld(), true);
		UGameplayStatics::OpenLevel(GetWorld(), CurrentLevelName, true);
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Safety Land!"));

	}
}

