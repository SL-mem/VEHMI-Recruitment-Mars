// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include <AssetRegistry/AssetDataTagMapSerializationDetails.h>
#include <Engine/RendererSettings.h>


AMyActor::AMyActor()
{
	PrimaryActorTick.bCanEverTick = true;
	k_p = 100;
}

void AMyActor::BeginPlay()
{
	Super::BeginPlay();

}

void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


FVector AMyActor::FollowTarget(float DeltaTime, FVector target, FVector robot_pos)
{
	FVector Err = target - robot_pos;

	FVector PositionCorrection = k_p * Err;

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


float AMyActor::CalculateAngleForXTranslation(float targetX, float robot_posX, float current_velocityX)
{
	float errorX = targetX - robot_posX;
	//float errorZ = targetZ - robot_posZ;
	//float theta_y = atan2(errorX, errorZ) * 180/PI;

	//return theta_y;

	float kp_orient = 0.5;
	float base_orient = 0;

	float desired_velocityX = errorX;

	float velocity_error = desired_velocityX - current_velocityX;

	float angleY = -kp_orient * velocity_error / 5 + base_orient;

	return angleY;
}


float AMyActor::CalculateAngleForYTranslation(float targetY, float robot_posY, float current_velocityY)
{
	float errorY = targetY - robot_posY;
	//float errorZ = targetZ - robot_posZ;
	//float theta_y = atan2(errorX, errorZ) * 180/PI;

	//return theta_y;

	float kp_orient = 0.5;
	float base_orient = 0;

	float desired_velocityY = errorY;

	float velocity_error = desired_velocityY - current_velocityY;

	float angleX = -kp_orient * velocity_error / 5 + base_orient;

	return angleX;
}

float AMyActor::Communication_delay(float DeltaTime, float err, float initial_pos)
{
	float StoredErrValue = initial_pos;

	ErrValues.Add(err);

	AccumulatedTime += DeltaTime;

	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Array Size: %d"), ErrValues.Num()));
	}*/

	if (AccumulatedTime >= 3.0f)
	{
		if (ErrValues.Num() > 0)
		{
			StoredErrValue = ErrValues[0];

			ErrValues.RemoveAt(0);
		}
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("StoredErrValue: %s"), *FString::SanitizeFloat(StoredErrValue)));
	return StoredErrValue;
}