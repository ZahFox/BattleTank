// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// How close can the AI tank get
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 8000;

private:

	APawn* PlayerTank = nullptr;

	UTankAimingComponent* AimingComponent = nullptr;
};
