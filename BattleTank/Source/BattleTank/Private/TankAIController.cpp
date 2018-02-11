// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = Cast<ATank>(GetPawn());
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//auto ControlledTank = Cast<ATank>(GetPawn());
	//auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerTank)
	{
		// Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
		ControlledTank->Fire();
	}
}
