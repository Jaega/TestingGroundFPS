// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"
#include "AI/Navigation/NavigationSystem.h"
#include "engine/world.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MinExtent = FVector(0, -2000, 0);
	MaxExtent = FVector(4000, 2000, 0);

	NavigationBoundsOffset = FVector(2000, 0, 0);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();	
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//Super::EndPlay(EndPlayReason);
	UE_LOG(LogTemp, Warning, TEXT("[%s] endplay"), *GetName());
	if (Pool && NavMeshBoundsVolume)
	{
		Pool->Return(NavMeshBoundsVolume);
	}
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATile::SetPool(UActorPool* PoolToSet)
{
	Pool = PoolToSet;
	PositionNavMeshBoundsVolume();
}

void ATile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = Pool->Checkout();
	if (!NavMeshBoundsVolume)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s]: Not enough volumes in pool"), *GetName());
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("[%s] checked out: [%s]"), *GetName(), *NavMeshBoundsVolume->GetName());
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOffset);
	UWorld* const World=GetWorld();
	auto NavSystem = World->GetNavigationSystem();
	NavSystem->Build();
}

TArray<FSpawnPosition> ATile::GenerateSpawnPositions(FSpawnParameter& SpawnParameter)
{
	TArray<FSpawnPosition> SpawnPositionsArray = TArray<FSpawnPosition>();
	auto count = FMath::RandRange(SpawnParameter.MinNum, SpawnParameter.MaxNum);
	for (size_t i = 0; i < count; i++)
	{
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(SpawnParameter.MinScale, SpawnParameter.MaxScale);
		if(FindEmptySpace(SpawnPosition.Location, SpawnParameter.Radius * SpawnPosition.Scale))
		{
			SpawnPosition.Rotation = FMath::RandRange(-180.f, 180.f);
			SpawnPositionsArray.Add(SpawnPosition);
		}
	}
	return SpawnPositionsArray;
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, FSpawnParameter& SpawnParameter)
{
	TArray<FSpawnPosition> SpawnPositionsArray = GenerateSpawnPositions(SpawnParameter);
	for (FSpawnPosition SpawnPosition: SpawnPositionsArray)
	{
		PositionActor(ToSpawn, SpawnPosition);
	}
	
}

void ATile::PositionActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition& SpawnPosition)
{
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);
	SpawnedActor->SetActorRelativeLocation(SpawnPosition.Location);
	SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	SpawnedActor->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
	SpawnedActor->SetActorScale3D(FVector(SpawnPosition.Scale));
}

void ATile::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, UPARAM(ref) FSpawnParameter& SpawnParameter)
{
	TArray<FSpawnPosition> SpawnPositionsArray = GenerateSpawnPositions(SpawnParameter);
	for (FSpawnPosition SpawnPosition: SpawnPositionsArray)
	{
		PositionAIPawn(ToSpawn, SpawnPosition);
	}
}

void ATile::PositionAIPawn(TSubclassOf<APawn> ToSpawn, FSpawnPosition& SpawnPosition)
{
	APawn* SpawnedAI = GetWorld()->SpawnActor<APawn>(ToSpawn);
	SpawnedAI->SetActorRelativeLocation(SpawnPosition.Location);
	SpawnedAI->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	SpawnedAI->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
	SpawnedAI->SpawnDefaultController();
	SpawnedAI->Tags.Add(FName("Enemy"));
}


bool ATile::FindEmptySpace(FVector& ResultPoint, float Radius)
{
	auto Bound = FBox(MinExtent, MaxExtent);
	
	const int MAX_ATTEMPTS = 100;
	for (size_t i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector CandidatePoint = FMath::RandPointInBox(Bound);
		if(CanSpawnAtLocation(CandidatePoint, Radius))
		{
			ResultPoint = CandidatePoint;
			return true;
		}
	}
	
	
	return false;
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

	return ! HasHit;
}





