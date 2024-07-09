// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TargetPosition = FVector(0.0, 0.0, 0.0);      // Initialisation of the variable, need to assign the position of the cube
	kp = 1.0;
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

	FollowTarget(DeltaTime);
}


void AMyActor::FollowTarget(float DeltaTime)
{
	RobotPosition = GetActorLocation();
	FVector Err = TargetPosition - RobotPosition;

	FVector PositionCorrection = kp * Err;

	SetActorLocation( RobotPosition + PositionCorrection );
}