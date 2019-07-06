// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "DetectingLight.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTINGGROUNDFPS_API UDetectingLight : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDetectingLight();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(class USpotLightComponent* SpotLightToSet);
	UFUNCTION(BlueprintCallable, Category = Rotation)
	void RefreshRandomElevatingSpeed();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)
	float TurningSpeed = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)
	int MaxTurningDegree= 180;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)
	int MinTurningDegree = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)
	float MaxElevatingSpeed = 20;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)
	int MaxElevationDegree = -10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)
	int MinElevationDegree = -65;
private:
	class USpotLightComponent* SpotLight;
	float RandomElevatingSpeed = 0;
	void Turn();
	void Elevate();
	// Variables that delay the light from reversing direction in case it gets "trapped" in the boundary
	int TurningWaitingCount = 0;
	int ElevationWaitingCount = 0;
};
