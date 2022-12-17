// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseFloor.generated.h"

class UBoxComponent;

UCLASS()
class MYPROJECT_API ABaseFloor : public AActor
{
	
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Triggers")
		UBoxComponent* Trigger;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Triggers")
		UBoxComponent* SpawnLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Triggers")
		UStaticMeshComponent* FloorMesh;

public:

	UBoxComponent* GetTrigger();
	UBoxComponent* GetSpawnLocation();
	UStaticMeshComponent* GetFloorMesh();


};
