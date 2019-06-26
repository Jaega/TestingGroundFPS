// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestingGroundFPSGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUNDFPS_API AInfiniteTerrainGameMode : public ATestingGroundFPSGameMode
{
	GENERATED_BODY()
public:
	AInfiniteTerrainGameMode();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pool)
	class UActorPool* NavMeshBoundsVolumePool;
	
public:
	UFUNCTION(BlueprintCallable, Category = BoundsPool)
	void PopulateBoundsVolumePool();
	

private:
	void AddToPool(class ANavMeshBoundsVolume *VolumeToAdd);
	
};
