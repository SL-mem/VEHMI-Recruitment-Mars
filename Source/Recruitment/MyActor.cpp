// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include <AssetRegistry/AssetDataTagMapSerializationDetails.h>
#include <Engine/RendererSettings.h>


AMyActor::AMyActor()
{
	PrimaryActorTick.bCanEverTick = true;

	PreviousError = 0.0f;
	Integral = 0.0f;
}

void AMyActor::BeginPlay()
{
	Super::BeginPlay();
}

void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AMyActor::GetThrust(float DeltaTime, float target, float robot_pos, float current_velocity, float kp, float ki, float kd, float base_value)
{

	float Error = Communication_delay(DeltaTime, target, robot_pos) - robot_pos;
	//float Error = target - robot_pos;

	//GEngine->AddOnScreenDebugMessage(-1, 500.f, FColor::Blue, FString::Printf(TEXT("error = desired_velocity: %s"), *FString::SanitizeFloat(Error)));

	float desired_velocity = Error;

	float velocity_error = desired_velocity - current_velocity;

	//GEngine->AddOnScreenDebugMessage(-1, 500.f, FColor::Green, FString::Printf(TEXT("current_velocity: %s"), *FString::SanitizeFloat(current_velocity)));
	//GEngine->AddOnScreenDebugMessage(-1, 500.f, FColor::Black, FString::Printf(TEXT("velocity_error = : %s"), *FString::SanitizeFloat(velocity_error)));

	Integral =+ velocity_error * DeltaTime;
	float Derivative = (velocity_error - PreviousError) * DeltaTime;

	float thrust_force = base_value + kp * velocity_error + ki * Integral + kd * Derivative;
	//GEngine->AddOnScreenDebugMessage(-1, 500.f, FColor::Yellow, FString::Printf(TEXT("Thrust %s"), *FString::SanitizeFloat(-thrust_force)));
	PreviousError = velocity_error;

	return thrust_force;
}


float AMyActor::CalculateAngleForXTranslation(float DeltaTime, float targetX, float robot_posX, float current_velocityX)
{
	//float errorX = targetX - robot_posX;
	float errorX = Communication_delay(DeltaTime, targetX, robot_posX) - robot_posX;
	//float errorZ = targetZ - robot_posZ;
	//float theta_y = atan2(errorX, errorZ) * 180/PI;

	//return theta_y;

	float kp_orient = 1.0;
	float base_orient = 0;

	float desired_velocityX = errorX;

	float velocity_error = desired_velocityX - current_velocityX;

	float angleY = -kp_orient * velocity_error / 5 + base_orient;

	return angleY;
}


float AMyActor::CalculateAngleForYTranslation(float DeltaTime, float targetY, float robot_posY, float current_velocityY)
{
	//float errorY = targetY - robot_posY;
	float errorY = Communication_delay(DeltaTime, targetY, robot_posY) - robot_posY;
	//float errorZ = targetZ - robot_posZ;
	//float theta_y = atan2(errorX, errorZ) * 180/PI;

	//return theta_y;

	float kp_orient = 1.0;
	float base_orient = 0;

	float desired_velocityY = errorY;

	float velocity_error = desired_velocityY - current_velocityY;

	float angleX = -kp_orient * velocity_error / 5 + base_orient;

	return angleX;
}

float AMyActor::Communication_delay(float DeltaTime, float target_pos, float initial_pos)
{
	float StoredTargetValue = initial_pos;

	TargetValues.Add(target_pos);

	AccumulatedTime += DeltaTime;

	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Array Size: %d"), ErrValues.Num()));
	}*/

	if (AccumulatedTime >= 3.0f)
	{
		if (TargetValues.Num() > 0)
		{
			StoredTargetValue = TargetValues[0];

			TargetValues.RemoveAt(0);
		}
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("StoredErrValue: %s"), *FString::SanitizeFloat(StoredErrValue)));
	return StoredTargetValue;
}