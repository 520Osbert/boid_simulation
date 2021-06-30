// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fish.h"
#include "Attractor.h"
#include "Distractor.h"
#include "EngineUtils.h"
#include "FishManager.generated.h"

UCLASS()
class UNDERWATER_API AFishManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFishManager();

	float minSpeed;
	float maxSpeed;

	float boidPerception;
	float boidAvoidance;
	float boidDistractRadius;

	float maxAlignment;
	float maxCohesion;
	float maxSeparation;
	float maxAttraction;

	FVector2D xBound;
	FVector2D yBound;
	FVector2D zBound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TArray<AFish*> Flock;

	AAttractor* attractor;
};
