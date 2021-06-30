// Fill out your copyright notice in the Description page of Project Settings.


#include "FishManager.h"

// Sets default values
AFishManager::AFishManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFishManager::BeginPlay()
{
	Super::BeginPlay();
	
	minSpeed = 300.0f;
	maxSpeed = 600.0f;

	boidPerception = 350.0f;
	boidAvoidance = 200.0f;
	boidDistractRadius = 300.0f;

	maxAlignment = 500.0f;
	maxCohesion = 500.0f;
	maxSeparation = 500.0f;
	maxAttraction = 500.0f;

	xBound = FVector2D(-1850.0f, 1050.0f);
	yBound = FVector2D(-1450.0f, 1450.0f);
	zBound = FVector2D(100.0f, 900.0f);

	UWorld* world = GetWorld();
	for (TActorIterator<AFish> It(world, AFish::StaticClass()); It; ++It)
	{
		AFish* fish = *It;
		if (fish != NULL)
		{
			Flock.Add(fish);
			fish->initialize(minSpeed, maxSpeed, boidPerception,
				boidAvoidance, boidDistractRadius, maxAlignment, maxCohesion,
				maxSeparation, maxAttraction, xBound, yBound, zBound);
		}
	}

	TActorIterator<AAttractor> It(world, AAttractor::StaticClass());
	attractor = *It;
}

// Called every frame
void AFishManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector attraction = attractor->location;

	int32 countFish = Flock.Num();
	if (countFish != 0)
	{
		for (int i = 0; i < countFish; i++)
		{
			AFish* fish = Flock[i];
			fish->Update(DeltaTime, Flock, attraction);
		}
	}
}

