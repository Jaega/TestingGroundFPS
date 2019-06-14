// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ChooseNextWayPoint.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUNDFPS_API UChooseNextWayPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) override;	
protected:
	TArray<AActor*> PatrolPoints;
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector IndexKey;
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector WayPointKey;
};
