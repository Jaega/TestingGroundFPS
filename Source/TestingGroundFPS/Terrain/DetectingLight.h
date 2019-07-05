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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)
	float TurningSpeed = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)
	float ElevatingSpeed;
private:
	class USpotLightComponent* SpotLight;
	void Turn();
};
