// Fill out your copyright notice in the Description page of Project Settings.


#include "Fish.h"

// Sets default values
AFish::AFish()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	location = FVector{ FMath::RandRange(-100.0f, 100.0f),
						FMath::RandRange(-100.0f, 100.0f),
						FMath::RandRange(-100.0f, 100.0f) };

	velocity = FVector{ FMath::RandRange(-1.0f, 1.0f),
						FMath::RandRange(-1.0f, 1.0f),
						FMath::RandRange(-1.0f, 1.0f) };
}

// Called when the game starts or when spawned
void AFish::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFish::initialize(float minSpd, float maxSpd, float perceptionRadius,
	float avoidanceRadius, float distract, float maxAlign, 
	float maxCohere, float maxSeparate, float maxAttract,
	FVector2D xBound, FVector2D yBound, FVector2D zBound)
{
	minSpeed = minSpd;
	maxSpeed = maxSpd;

	perception = perceptionRadius;
	avoidance = avoidanceRadius;
	distractRadius = distract;

	maxAlignment = maxAlign;
	maxCohesion = maxCohere;
	maxSeparation = maxSeparate;
	maxAttraction = maxAttract;

	xRange = xBound;
	yRange = yBound;
	zRange = zBound;
}

void AFish::Update(float DeltaTime, TArray<AFish*> Flock, FVector attracting)
{
	FVector align = alignment(Flock);
	FVector cohere = coherence(Flock);
	FVector separate = separation(Flock);
	FVector attract = distraction(attracting);

	// 设质量为1，F=ma，受力与加速度成正比
	acceleration = align + cohere + 1.5 * separate + 2 * attract;
	// Delta(速度) = 加速度 * 时间
	velocity += acceleration * DeltaTime;
	// 速度clamped，限定在[minSpeed, maxSpeed]范围之间
	velocity = velocity.GetClampedToSize(minSpeed, maxSpeed);
	// Delta(位置) = 速度 * 时间
	location += velocity * DeltaTime;
	SetActorLocation(location);
	checkEdge();
}

FVector AFish::alignment(TArray<AFish*> Flock)
{
	FVector steering{ 0.0f, 0.0f, 0.0f };
	int32 fishPercepted = 0;

	for (int i = 0; i < Flock.Num(); i++)
	{
		float d = FVector::Dist(location, Flock[i]->location);
		if (Flock[i] != this && d < perception)
		{
			steering += Flock[i]->velocity;
			fishPercepted++;
		}
	}

	if (fishPercepted > 0)
	{
		steering /= fishPercepted;
		steering = steering / steering.Size() * maxSpeed - velocity;
		steering = steering.GetClampedToMaxSize(maxAlignment);
	}

	return steering;
}

FVector AFish::coherence(TArray<AFish*> Flock)
{
	FVector steering{ 0.0f, 0.0f, 0.0f };
	int32 fishPercepted = 0;

	for (int i = 0; i < Flock.Num(); i++)
	{
		float d = FVector::Dist(location, Flock[i]->location);
		if (Flock[i] != this && d < perception)
		{
			steering += Flock[i]->location;
			fishPercepted++;
		}
	}

	if (fishPercepted > 0)
	{
		steering /= fishPercepted;
		steering -= location;
		steering = steering / steering.Size() * maxSpeed - velocity;
		steering = steering.GetClampedToMaxSize(maxSeparation);
	}

	return steering;
}

FVector AFish::separation(TArray<AFish*> Flock)
{
	FVector steering{ 0.0f, 0.0f, 0.0f };
	int32 fishPercepted = 0;

	for (int i = 0; i < Flock.Num(); i++)
	{
		float d = FVector::Dist(location, Flock[i]->location);
		if (Flock[i] != this && d < perception)
		{
			if (d < avoidance)
			{
				FVector offset = location - Flock[i]->location;
				float sqrDist = offset.SizeSquared();
				// 因为要规避其他个体，受力与距离成反比
				steering += offset / sqrDist;
				fishPercepted++;
			}
		}
	}

	if (fishPercepted > 0)
	{
		steering = steering / steering.Size() * maxSpeed - velocity;
		steering = steering.GetClampedToMaxSize(maxSeparation);
	}

	return steering;
}

// 边缘检测
void AFish::checkEdge()
{
	if (location.X > xRange.Y)
		location.X = xRange.X;
	else if (location.X < xRange.X)
		location.X = xRange.Y;

	if (location.Y > yRange.Y)
		location.Y = yRange.X;
	else if (location.Y < yRange.X)
		location.Y = yRange.Y;

	if (location.Z > zRange.Y)
		location.Z = zRange.X;
	else if (location.Z < zRange.X)
		location.Z = zRange.Y;
}

// 额外的吸引物受力

FVector AFish::attraction(FVector vector)
{
	FVector steering = vector;
	steering -= location;
	steering = steering / steering.Size() * maxSpeed - velocity;
	steering = steering.GetClampedToMaxSize(maxAttraction);
	return steering;
}

FVector AFish::distraction(FVector vector)
{
	float d = FVector::Dist(location, vector);
	if (d < distractRadius)
	{
		FVector steering = vector;
		steering = 2 * location - steering;
		steering -= location;
		steering = steering / steering.Size() * maxSpeed - velocity;
		steering = steering.GetClampedToMaxSize(maxAttraction);

		return steering;
	}
	else 
	{
		return FVector(0);
	}
}