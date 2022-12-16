// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticFurniture_1x1.h"

// Sets default values
AStaticFurniture_1x1::AStaticFurniture_1x1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStaticFurniture_1x1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStaticFurniture_1x1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

