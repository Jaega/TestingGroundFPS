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

USTRUCT(BlueprintType)
struct FSpawnParameter
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SpawnParameter)
	int MinNum = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SpawnParameter)
	int MaxNum = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SpawnParameter)
	float Radius = 500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SpawnParameter)
	float MinScale = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SpawnParameter)
	float MaxScale = 1;
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

	UFUNCTION(BlueprintCallable, Category = Spawning)
	void PlaceActors(TSubclassOf<AActor> ToSpawn, UPARAM(ref) FSpawnParameter& SpawnParameter);
	UFUNCTION(BlueprintCallable, Category = Spawning)
	void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, UPARAM(ref) FSpawnParameter& SpawnParameter);
	
	UFUNCTION(BlueprintCallable, Category = Pool)
	void SetPool(UActorPool* PoolToSet);
	
private:
	TArray<FSpawnPosition> GenerateSpawnPositions(FSpawnParameter& SpawnParameter);
	void PositionActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition& SpawnPosition);
	void PositionAIPawn(TSubclassOf<APawn> ToSpawn, FSpawnPosition& SpawnPosition);
	void PositionNavMeshBoundsVolume();

	bool CanSpawnAtLocation(FVector Location, float Radius);
	bool FindEmptySpace(FVector& ResultPoint, float Radius);

	class UActorPool* Pool;
	AActor* NavMeshBoundsVolume;
};
