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
	CastSphere(GetActorLocation() + FVector(0,0,100), 100);
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int Min, int Max)
{
	auto MinPoint = FVector(0, -2000, 0);
	auto MaxPoint = FVector(4000, 2000, 0);
	auto Bound = FBox(MinPoint, MaxPoint);
	auto count = FMath::RandRange(Min, Max);
	for (size_t i = 0; i < count; i++)
	{
		auto SpawnPoint = FMath::RandPointInBox(Bound);
		UE_LOG(LogTemp, Warning, TEXT("Spawn Actor at: %s"), *SpawnPoint.ToString())
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);

		SpawnedActor->SetActorRelativeLocation(SpawnPoint);
		SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	}
	
	
}

bool ATile::CastSphere(FVector Location, float Radius)
{
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Location,
		Location,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2, // Spawn Channel: ignore collision with Ground and Trigger
		FCollisionShape::MakeSphere(Radius)
	);
	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;

	DrawDebugCapsule(
    	GetWorld(),
    	Location,
		0,
    	Radius,
    	FQuat::Identity,
    	ResultColor,
    	true,
    	100
	);
	return HasHit;
}

