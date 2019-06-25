// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "GrassComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTINGGROUNDFPS_API UGrassComponent : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = Spawning)
	FBox SpawnExtent;
	UPROPERTY(EditDefaultsOnly, Category = Spawning)
	int SpawnCount;
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void PlaceGrass();	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
