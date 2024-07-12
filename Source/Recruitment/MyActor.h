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
	float k_p;					// Proportional gain for the P-Controller

	UFUNCTION(BlueprintCallable, Category = "Control")
	FVector FollowTarget(float DeltaTime, FVector target, FVector robot_pos);   // function that will be created to implement the controller and to follow the target

	UFUNCTION(BlueprintCallable, Category = "Control")
	float GetThrust(float DeltaTime, float target, float robot_pos, float current_velocity, float kp, float base_value);
};
