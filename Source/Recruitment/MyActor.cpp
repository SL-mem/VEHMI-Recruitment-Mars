// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//TargetPosition = FVector(0.0, 0.0, 0.0);      // Initialisation of the variable, need to assign the position of the cube
	k_p = 100;
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

	//Communication_delay(DeltaTime);
	//FollowTarget(DeltaTime);
}


FVector AMyActor::FollowTarget(float DeltaTime, FVector target, FVector robot_pos)
{
	//RobotPosition = GetActorLocation();
	//FVector Err = TargetPosition - RobotPosition;
	FVector Err = target - robot_pos;

	FVector PositionCorrection = k_p * Err;

	//SetActorLocation( RobotPosition + PositionCorrection );
	FVector newpos = target;

	return newpos;
}

float AMyActor::GetThrust(float DeltaTime, float target, float robot_pos, float current_velocity, float kp, float base_value)
{
	float Error = target - robot_pos;

	float stored_error = Communication_delay(DeltaTime, Error);

	/*for (0.0; 3.0; DeltaTime) 
	{
		float desired_velocity = stored_error[i];

		float velocity_error = desired_velocity - current_velocity;

		float thrust_force = base_value + kp * velocity_error;
	}*/
	
	float desired_velocity = stored_error;

	float velocity_error = desired_velocity - current_velocity;

	float thrust_force = base_value + kp * velocity_error;

	return thrust_force;
}


float AMyActor::Communication_delay(float DeltaTime, float err)
{
	float StoredErrValue = 0.0;

	//ErrValues.Add(err);

	//AccumulatedTime += DeltaTime;


	if (AccumulatedTime < 3.0)
	{
		ErrValues.Add(err);
		AccumulatedTime += DeltaTime;

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("size: %s"), *FString::SanitizeFloat(ErrValues[0])));

	}
	if (AccumulatedTime >= 3.0)
	{
		//StoredErrValue = 500;

		//size = sizeof(ErrValues);

		for (int j=0; j < sizeof(ErrValues) - 1; j++)
		{
			ErrValues[j] = ErrValues[j + 1];
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("size: %s"), *FString::SanitizeFloat(sizeof(ErrValues))));
		// When printed, size = 16.0 during whole simulation

		ErrValues.Add(err);

		StoredErrValue = ErrValues[0];
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("StoredErrValue: %s"), *FString::SanitizeFloat(StoredErrValue)));
	return StoredErrValue;
	//return ErrValues;
}