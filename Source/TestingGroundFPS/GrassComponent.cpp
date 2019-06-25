// Fill out your copyright notice in the Description page of Project Settings.

#include "GrassComponent.h"

void UGrassComponent::PlaceGrass()
{
    if (SpawnExtent == NULL) { return; }
    for (size_t i = 0; i < SpawnCount; i++)
    {
        FVector SpawnPoint = FMath::RandPointInBox(SpawnExtent);
        AddInstance(FTransform(SpawnPoint));
    }
}

// Called when the game starts or when spawned
void UGrassComponent::BeginPlay()
{
	Super::BeginPlay();	
    PlaceGrass();
}
