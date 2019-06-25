// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "EngineUtils.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"

void AInfiniteTerrainGameMode::BeginPlay()
{
    Super::BeginPlay();
    PopulateBoundsVolumePool();
    
}

void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
    TActorIterator<ANavMeshBoundsVolume> VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());

	while (VolumeIterator)
	{
		ANavMeshBoundsVolume* FoundVolume = *VolumeIterator;
        AddToPool(FoundVolume);
		++VolumeIterator;
	}    
}

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume *VolumeToAdd)
{
    UE_LOG(LogTemp, Warning, TEXT("Found actor: %s"), *VolumeToAdd->GetName());
}


