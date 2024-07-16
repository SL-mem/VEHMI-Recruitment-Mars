// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include <AssetRegistry/AssetDataTagMapSerializationDetails.h>
#include <Engine/RendererSettings.h>

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
	float Error = Communication_delay(DeltaTime, target, robot_pos) - robot_pos;

	float desired_velocity = Error;

	float velocity_error = desired_velocity - current_velocity;

	float thrust_force = base_value + kp * velocity_error;

	return thrust_force;
}


float AMyActor::Communication_delay(float DeltaTime, float err, float initial_pos)
{
	float StoredErrValue = initial_pos;

	ErrValues.Add(err);

	AccumulatedTime += DeltaTime;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Array Size: %d"), ErrValues.Num()));
	}

	if (AccumulatedTime >= 3.0f)
	{
		if (ErrValues.Num() > 0)
		{
			StoredErrValue = ErrValues[0];

			ErrValues.RemoveAt(0);
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("StoredErrValue: %s"), *FString::SanitizeFloat(StoredErrValue)));
	return StoredErrValue;
}