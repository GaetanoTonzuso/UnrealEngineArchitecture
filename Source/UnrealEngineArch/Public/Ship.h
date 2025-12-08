#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "Ship.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class UNREALENGINEARCH_API AShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShip();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NotifyHit(class UPrimitiveComponent* MyComp,
		AActor* Other,
		class UPrimitiveComponent* OtherComp,
		bool bSelfMoved,
		FVector HitLocation,
		FVector HitNormal,
		FVector NormalImpulse,
		const FHitResult& Hit);

	bool IsLandedSafely();

	void HandleShipLand();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship | Movement")
	float ImpulseStrenght = 10.f;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Ship | Movement")
	float TorqueStrenght = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship | Graphics")
	UStaticMeshComponent* ShipMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship | Input")
	UInputMappingContext* ShipMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship | Input")
	UInputAction* PropelInput;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Ship | Input")
	UInputAction* RotateInput;

	void PropelUp(const FInputActionValue& Value);
	void RotateShip(const FInputActionValue& Value);

private:	

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;
};
