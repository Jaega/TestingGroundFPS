// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

USTRUCT(BlueprintType)
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()
	FVector Location;
	float Rotation;
	float Scale;
};

UCLASS()
class TESTINGGROUNDFPS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = Spawning)
	FVector MinExtent;
	UPROPERTY(EditDefaultsOnly, Category = Spawning)
	FVector MaxExtent;

	UPROPERTY(EditDefaultsOnly, Category = Navigation)
	FVector NavigationBoundsOffset;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int Min = 1, int Max = 1, float Radius = 500, float MinScale = 1, float MaxScale = 1);
	
	UFUNCTION(BlueprintCallable, Category = Pool)
	void SetPool(UActorPool* PoolToSet);
	

private:
	bool CanSpawnAtLocation(FVector Location, float Radius);
	bool FindEmptySpace(FVector& ResultPoint, float Radius);
	TArray<FSpawnPosition> GenerateSpawnPositions(int MinNum, int MaxNum, float Radius, float MinScale, float MaxScale);
	void PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition& SpawnPosition);
	void PositionNavMeshBoundsVolume();
	class UActorPool* Pool;
	AActor* NavMeshBoundsVolume;
};
