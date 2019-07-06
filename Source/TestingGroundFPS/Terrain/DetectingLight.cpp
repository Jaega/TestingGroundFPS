// Fill out your copyright notice in the Description page of Project Settings.

#include "DetectingLight.h"
#include "Components/SpotLightComponent.h"

// Sets default values for this component's properties
UDetectingLight::UDetectingLight()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDetectingLight::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDetectingLight::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Turn();
	Elevate();
	// ...
}

void UDetectingLight::Initialize(USpotLightComponent* SpotLightToSet)
{
	if (!ensure(SpotLightToSet)) { return; }
	SpotLight = SpotLightToSet;
	
}

void UDetectingLight::Turn()
{
	if (RelativeRotation.Yaw >= MaxTurningDegree || RelativeRotation.Yaw <= MinTurningDegree)
	{
		TurningSpeed = -TurningSpeed;
	}
	
    float RotationChange = TurningSpeed * GetWorld()->DeltaTimeSeconds;
    float NewRotation = RelativeRotation.Yaw + RotationChange;

    SetRelativeRotation(FRotator(0, NewRotation, 0));
}

void UDetectingLight::Elevate()
{
	if (!ensure(SpotLight)) { return; }
	if (SpotLight->RelativeRotation.Pitch <= MinElevationDegree || SpotLight->RelativeRotation.Pitch >= MaxElevationDegree)
	{
		RandomElevatingSpeed = -RandomElevatingSpeed;
	}
    float ElevationChange = RandomElevatingSpeed * GetWorld()->DeltaTimeSeconds;
    float RawNewElevation = SpotLight->RelativeRotation.Pitch + ElevationChange;
    float Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegree, MaxElevationDegree);
    SpotLight->SetRelativeRotation(FRotator(Elevation, 0, 0));
	RefreshRandomElevatingSpeed();
}

void UDetectingLight::RefreshRandomElevatingSpeed()
{
	RandomElevatingSpeed = FMath::RandRange(-MaxElevatingSpeed, MaxElevatingSpeed);
}
