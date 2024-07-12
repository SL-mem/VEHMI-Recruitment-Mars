// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TargetPosition = FVector(0.0, 0.0, 0.0);      // Initialisation of the variable, need to assign the position of the cube
	kp = 100;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FollowTarget(DeltaTime);
}


FVector AMyActor::FollowTarget(float DeltaTime, FVector target, FVector robot_pos)
{
	//RobotPosition = GetActorLocation();
	//FVector Err = TargetPosition - RobotPosition;
	FVector Err = target - robot_pos;

	FVector PositionCorrection = kp * Err;

	//SetActorLocation( RobotPosition + PositionCorrection );
	FVector newpos = target;

	return newpos;
}

float AMyActor::GetThrust(float DeltaTime, float target, float robot_pos, float current_velocity, float distance_threshold)
{
	float Error = target - robot_pos;

	float desired_velocity = Error;

	float velocity_error = desired_velocity - current_velocity;

	//float thrust_force = kp * desired_velocity;

	//float thrust_force = base_value + kp * velocity_error;

	float thrust_force = 1000 + kp * velocity_error;
	//if ((Error == distance_threshold && Error > 0) or ((-Error == distance_threshold && Error < 0)))
	//{
		//float ScaleFactor = Error / distance_threshold;
		//thrust_force *= ScaleFactor;
		//thrust_force = -50 * thrust_force;
	//}


	return thrust_force;
}