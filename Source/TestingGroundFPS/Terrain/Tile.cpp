// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "DrawDebugHelpers.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	//CanSpawnAtLocation(GetActorLocation() + FVector(0,0,100), 100);
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int Min, int Max, float Radius)
{
	auto count = FMath::RandRange(Min, Max);
	for (size_t i = 0; i < count; i++)
	{
		FVector SpawnPoint;
		if(FindEmptySpace(SpawnPoint, Radius))
		{
			PlaceActor(ToSpawn, SpawnPoint);
		}
	}
}

bool ATile::FindEmptySpace(FVector& ResultPoint, float Radius)
{
	auto MinPoint = FVector(0, -2000, 0);
	auto MaxPoint = FVector(4000, 2000, 0);
	auto Bound = FBox(MinPoint, MaxPoint);
	
	const int MAX_ATTEMPTS = 100;
	for (size_t i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector CandidatePoint = FMath::RandPointInBox(Bound);
		if(CanSpawnAtLocation(CandidatePoint, Radius))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Not Empty"));
			ResultPoint = CandidatePoint;
			return true;
		}
	}
	
	
	return false;
}


void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint)
{
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);
	SpawnedActor->SetActorRelativeLocation(SpawnPoint);
	SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		GlobalLocation,
		GlobalLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2, // Spawn Channel: ignore collision with Ground and Trigger
		FCollisionShape::MakeSphere(Radius)
	);
	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;

	DrawDebugCapsule(
    	GetWorld(),
    	GlobalLocation,
		0,
    	Radius,
    	FQuat::Identity,
    	ResultColor,
    	true,
    	Radius
	);
	return ! HasHit;
}



