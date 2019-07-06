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
	if (TurningWaitingCount == 10)
	{
		if ((int)RelativeRotation.Yaw >= MaxTurningDegree || (int)RelativeRotation.Yaw <= MinTurningDegree)
		{
			TurningSpeed = -TurningSpeed;
		}
		TurningWaitingCount = 0;
	}
	
    float RotationChange = TurningSpeed * GetWorld()->DeltaTimeSeconds;
    float NewRotation = RelativeRotation.Yaw + RotationChange;

    SetRelativeRotation(FRotator(0, NewRotation, 0));
	TurningWaitingCount++;
}

void UDetectingLight::Elevate()
{
	if (!ensure(SpotLight)) { return; }
	if (ElevationWaitingCount == 10)
	{
		if ((int)SpotLight->RelativeRotation.Pitch <= MinElevationDegree || (int)SpotLight->RelativeRotation.Pitch >= MaxElevationDegree)
		{
			RandomElevatingSpeed = -RandomElevatingSpeed;
		}
		ElevationWaitingCount = 0;
	}
	
	
    float ElevationChange = RandomElevatingSpeed * GetWorld()->DeltaTimeSeconds;
    float RawNewElevation = SpotLight->RelativeRotation.Pitch + ElevationChange;
    float Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegree, MaxElevationDegree);
    SpotLight->SetRelativeRotation(FRotator(Elevation, 0, 0));
	ElevationWaitingCount++;
}

void UDetectingLight::RefreshRandomElevatingSpeed()
{
	RandomElevatingSpeed = FMath::RandRange(-MaxElevatingSpeed, MaxElevatingSpeed);
}
