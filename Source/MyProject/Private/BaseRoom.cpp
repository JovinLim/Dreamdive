// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseRoom.h"

#include "Components/BoxComponent.h"

// Sets default values
ABaseRoom::ABaseRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseRoom::BeginPlay()
{
	Super::BeginPlay();

	if (Trigger != nullptr)
		Trigger->bHiddenInGame = true;
	
}

// Called every frame
void ABaseRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UBoxComponent* ABaseRoom::GetTrigger()
{
	return Trigger;
}

UBoxComponent* ABaseRoom::GetSpawnLocation()
{
	return SpawnLocation;
}

UStaticMeshComponent* ABaseRoom::GetFloorMesh()
{
	return FloorMesh;
}

