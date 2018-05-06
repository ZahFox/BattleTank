// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; // Out parameter
	
	// Get world location of linetrace through crosshair
	if (GetSightRayHitLocation(HitLocation)) // Has "side-effect", is going to line trace
	{
		AimingComponent->AimAt(HitLocation);
	}
}


// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Calculate the current viewport size
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	// Calculate the screen position of the crosshair in pixel coordinates
	FVector2D ScreenLocation{ ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation };

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along LookDirection, and see what we hit (up to a max range)
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	return false;
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
	   )
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);
	return true;
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const 
{
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		OutLookDirection
	);
}
