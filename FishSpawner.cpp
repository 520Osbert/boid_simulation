// Fill out your copyright notice in the Description page of Project Settings.


#include "FishSpawner.h"

// Sets default values
AFishSpawner::AFishSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFishSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	const FVector Origin(0);
	const FRotator Rotation = GetActorRotation();

	for (int i = 0; i < NumberOfFish; i++)
	{
		GetWorld()->SpawnActor<AActor>(FishToSpawn, Origin, Rotation);
	}

	FVector zero(0, 0, 0);
	GetWorld()->SpawnActor<AActor>(ManagerToSpawn, zero, Rotation);
}

// Called every frame
void AFishSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

