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
	float AccumulatedTime=0.0f;
	TArray<float> TargetValues;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Control")
	FVector TargetPosition;      // Target position = position of the cube to reach

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Control")
	FVector RobotPosition;

	UPROPERTY(BluePrintReadWrite, EditAnywhere, Category = "Control")
	FVector NewPos;


	float PreviousError;
	float Integral;

	UFUNCTION(BlueprintCallable, Category = "Control")
	float GetThrust(float DeltaTime, float target, float robot_pos, float current_velocity, float kp, float ki, float kd, float base_value);


	UFUNCTION(BlueprintCallable, Category = "Control")
	float Communication_delay(float DeltaTime, float target_pos, float initial_pos);

	UFUNCTION(BlueprintCallable, Category = "Control")
	float CalculateAngleForXTranslation(float DeltaTIme, float targetX, float robot_posX, float current_velocityX);

	UFUNCTION(BlueprintCallable, Category = "Control")
	float CalculateAngleForYTranslation(float DeltaTime, float targetY, float robot_posY, float current_velocityY);
};
