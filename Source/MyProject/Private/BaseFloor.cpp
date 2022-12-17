// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseFloor.h"

#include "Components/BoxComponent.h"

// Sets default values
ABaseFloor::ABaseFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseFloor::BeginPlay()
{
	Super::BeginPlay();

	if (Trigger != nullptr)
		Trigger->bHiddenInGame = true;
	
}

// Called every frame
void ABaseFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UBoxComponent* ABaseFloor::GetTrigger()
{
	return Trigger;
}

UBoxComponent* ABaseFloor::GetSpawnLocation()
{
	return SpawnLocation;
}

UStaticMeshComponent* ABaseFloor::GetFloorMesh()
{
	return FloorMesh;
}
