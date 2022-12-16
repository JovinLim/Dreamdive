// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Templates/Tuple.h"
#include "RoomEnd.generated.h"


class ABaseRoom;
class AStaticFurniture_1x1;
class Pocket;

UCLASS()
class CPLUSPLUS_PROJECT_API ARoomEnd : public AActor
{

	GENERATED_BODY()


public:	
	// Sets default values for this actor's properties
	ARoomEnd();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
		void SpawnFloor(bool IsFirst);

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

//	UFUNCTION()
		TArray<TArray<int32>> GenerateRMatrix(int RoomWidth, int RoomLength);

//	UFUNCTION()
		TSet<TArray<int32>> GenerateCirculation(TArray<int32> EntranceCoords, TArray<int32> ExitCoords, int RoomWidth, int RoomLength, int CirculationType);

		TMap<int32, Pocket> GeneratePockets(TSet<TArray<int32>> Emptycoords);

		void RemoveSubrectangles(TMap<int32, Pocket> PocketList);

protected:


	APawn* Player;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABaseRoom> TestRoom;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AStaticFurniture_1x1> CirculationSpace;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AStaticFurniture_1x1> PocketObject;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AStaticFurniture_1x1> PocketObject1;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<AStaticFurniture_1x1> PocketObject2;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<AStaticFurniture_1x1> PocketObject3;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AStaticFurniture_1x1> PocketObject4;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AStaticFurniture_1x1> PocketObject5;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AStaticFurniture_1x1> PocketObject6;

	UPROPERTY(EditAnywhere)
		int XTiles;

	UPROPERTY(EditAnywhere)
		int YTiles;

	UPROPERTY(EditAnywhere)
		int MaxLoopCount;


	TArray<ABaseRoom*> LevelList;





public:

	int RandomPocket;

	FVector SpawnLocation = FVector();
	FRotator SpawnRotation = FRotator();
	FActorSpawnParameters SpawnInfo = FActorSpawnParameters();
	FVector FloorSize = FVector();
	FVector FloorScale = FVector();
	TArray<TArray<int32>> RandomMatrix;

	int OffsetCorrection(float* offset);

};


