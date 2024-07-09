// Fill out your copyright notice in the Description page of Project Settings.
// header file, "declare" all the functions and variables there

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class RECRUITMENT_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Control")
	FVector TargetPosition;      // Target position = position of the cube to reach

	FVector RobotPosition;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Control")
	float kp;					// Proportional gain for the P-Controller

	UFUNCTION(BlueprintCallable, Category = "Control")
	void FollowTarget(float DeltaTime);   // function that will be created to implement the controller and to follow the target

};
