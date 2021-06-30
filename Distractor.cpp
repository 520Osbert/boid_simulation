// Fill out your copyright notice in the Description page of Project Settings.


#include "Distractor.h"

// Sets default values
ADistractor::ADistractor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADistractor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADistractor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	location = GetActorLocation();
}

