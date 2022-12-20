// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"
#include "MapGenerator.generated.h"

//USTRUCT(BlueprintType)
//struct FMatrixInformation
//{
//	GENERATED_BODY()
//
//		//UPROPERTY(EditAnywhere,BlueprintReadWrite)
//			//TMap<int32,TArray<int>> m_id;
//
//		bool run;
//
//	//Default Constructor
//	FMatrixInformation()
//	{
//
//		run = false;
//
//	}
//};

UCLASS()
class MYPROJECT_API AMapGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Matrix creation
	TArray<TArray<int>> m_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<int> wallLoc;

	TArray<TArray<int>> wallRot;

	TMap<int, TArray<TArray<int>>> Room_Properties;

	//FMatrixInformation MatrixInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 y_ax = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 x_ax = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 cell_size = 20;

	UFUNCTION(BlueprintCallable, Category = "Matrix Generation")
		void Caller();

	//UFUNCTION(BlueprintCallable, Category = "Matrix Generation")
	bool checkvalid(TArray<TArray<int>>& matrix, TArray<TArray<int>>& target, int target_y, int target_x);

	TArray<int> adjCheck(TArray<TArray<int>>& matrix, int target_y, int target_x);

	bool checkvisited(TArray<TArray<int>>& matrix, TArray<TArray<int>>& target, int target_y, int target_x);

	void InstantiateMatrix(TArray<TArray<int>>& matrix, int y_ax, int x_ax, int cell_size);

	void PopulateRooms(TMap<int, TArray<TArray<int>>>& Room_Prop, TArray<TArray<int>>& matrix, int y_ax, int x_ax, int cell_size);

	void PrintMatrix(TArray<TArray<int>>& matrix);

	void PrintMapInfo(TMap<int, TArray<TArray<int>>>& Room_Prop);

	void UpdateMatrix(TMap<int, TArray<TArray<int>>>& Room_Prop, TArray<TArray<int>>& matrix);

	void UpdateRooms_FromMatrix(TMap<int, TArray<TArray<int>>>& Room_Prop, TArray<TArray<int>>& matrix);

	void AddDoors(TMap<int, TArray<TArray<int>>>& Room_Prop, TArray<TArray<int>>& matrix);

	void RemoveSpace(TArray<TArray<int>>& matrix, int iterations);

	void MapRemove(TMap<int, TArray<TArray<int>>>& Room_Prop, int itr);

	TArray<TArray<int>> CreateVoid();

	void FixRoom(TArray<TArray<int>>& matrix);

	void checkWall(TArray<TArray<int>>& matrix, TArray<int>& loc, TArray<TArray<int>>& rot);

	UFUNCTION(BlueprintCallable, Category = "Spawner")
		TArray<int> GetScale(int target_dimX, int target_dimY);

	void spawnWall();

	void spawnFloor();

	void scaleObject(AStaticMeshActor* actor, TArray<int>& dimensions, TArray<int>& target);

//MESHES AND SHIT
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* wall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* floor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> floorDim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<int> wallDim;
};
