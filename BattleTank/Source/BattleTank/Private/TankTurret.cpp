// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"


void UTankTurret::Elevate(float RelativeSpeed)
{
	// Move barrel the right amount this frame
	// Given a max elevation speed, and the frame time

	auto ElevationChange = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	SetRelativeRotation(FRotator(
		RawNewElevation,
		0,
		0
	));
}


