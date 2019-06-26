// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorPool.h"


// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AActor* UActorPool::Checkout()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] checkout."), *GetName());
	return nullptr;
}

void UActorPool::Return(AActor* ActorToReturn)
{
	if (!ActorToReturn)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] receive return: NULL."), *GetName());
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("[%s] receive return: %s."), *GetName(), *ActorToReturn->GetName());
}

void UActorPool::Add(AActor* ActorToAdd)
{
	if (!ActorToAdd)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] Add: NULL."), *GetName());
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("[%s] Add %s."), *GetName(), *ActorToAdd->GetName());
}


