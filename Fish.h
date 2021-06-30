// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"
#include "Fish.generated.h"

UCLASS()
class UNDERWATER_API AFish : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFish();
	FVector location;
	FVector velocity;
	FVector acceleration;

	float minSpeed;
	float maxSpeed;

	float perception;
	float avoidance;
	float distractRadius;

	float maxAlignment;
	float maxCohesion;
	float maxSeparation;
	float maxAttraction;

	FVector2D xRange;
	FVector2D yRange;
	FVector2D zRange;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void initialize(float minSpd, float maxSpd, float perceptionRadius,
		float avoidanceRadius, float distract, float maxAlign, 
		float maxCohere, float maxSeparate, float maxAttract,
		FVector2D xBound, FVector2D yBound, FVector2D zBound);

	void checkEdge();

	void Update(float DeltaTime, TArray<AFish*> Flock, FVector attraction);

	FVector alignment(TArray<AFish*> Flock);

	FVector coherence(TArray<AFish*> Flock);

	FVector separation(TArray<AFish*> Flock);

	FVector attraction(FVector vector);

	FVector distraction(FVector vector);
};
