// Copyright ZahFox Tales

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;
class UStaticMeshComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASprungWheel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* PhysicsConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Wheel = nullptr;

	void SetupConstraint();
};
