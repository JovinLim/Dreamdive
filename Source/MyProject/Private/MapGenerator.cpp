// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGenerator.h"
#include <iostream>
#include <stdlib.h>

// Sets default values
AMapGenerator::AMapGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//wall->SetStaticMesh(Asset.Object);

}

// Called when the game starts or when spawned
void AMapGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapGenerator::Caller()
{
	FString test = "test";
	UE_LOG(LogTemp, Warning, TEXT("The vector is: %s"), *test);
	InstantiateMatrix(m_id, y_ax, x_ax, cell_size);
	PopulateRooms(Room_Properties, m_id, y_ax, x_ax, cell_size);
	MapRemove(Room_Properties, 10);
	//checkWall(m_id, wallLoc, wallRot);

	UpdateMatrix(Room_Properties, m_id);
	AddDoors(Room_Properties, m_id);
	UpdateRooms_FromMatrix(Room_Properties, m_id);
	PrintMatrix(m_id);
	//PrintMapInfo(Room_Properties);
	FVector ActorLocation = FVector(0.f, 0.f, 0.f);
	//spawnWall(ActorLocation);
	spawnFloor();
}

TArray<int> AMapGenerator::adjCheck(TArray<TArray<int>>& matrix, int target_y, int target_x) {
	// START FROM BOTTOM LEFT, CLOCKWISE
	int rows = matrix.Num() - 1;
	int cols = matrix[0].Num() - 1;
	TArray<int> adjacents;
	TArray<TArray<int>> coordinates;
	for (int i = 0; i < 8; i++) {
		TArray<int> target;
		if (i == 0) {
			target.Add(target_y - 1);
			target.Add(target_x - 1);
		}
		else if (i == 1) {
			target.Add(target_y);
			target.Add(target_x - 1);
		}
		else if (i == 2) {
			target.Add(target_y + 1);
			target.Add(target_x - 1);
		}
		else if (i == 3) {
			target.Add(target_y + 1);
			target.Add(target_x);
		}
		else if (i == 4) {
			target.Add(target_y + 1);
			target.Add(target_x + 1);
		}
		else if (i == 5) {
			target.Add(target_y);
			target.Add(target_x + 1);
		}
		else if (i == 6) {
			target.Add(target_y - 1);
			target.Add(target_x + 1);
		}
		else if (i == 7) {
			target.Add(target_y - 1);
			target.Add(target_x);
		}
		coordinates.Add(target);
	}
	for (TArray<int> coord : coordinates) {
		if (coord[0] < 0 || coord[1] < 0 || coord[0] > rows || coord[1] > cols) {
			adjacents.Add(-1);
		}
		else {
			adjacents.Add(matrix[coord[0]][coord[1]]);
		}
	}

	return adjacents;
}

bool AMapGenerator::checkvalid(TArray<TArray<int>>& matrix, TArray<TArray<int>>& target, int target_y, int target_x) {
	int matrix_rows = matrix.Num();
	int matrix_cols = matrix[0].Num();
	int target_rows = target.Num();
	int target_cols = target[0].Num();

	if (target_y + target_rows >= matrix_rows || target_x + target_cols >= matrix_cols || target_x < 0 || target_y < 0) {
		return false;
	}

	else {
		for (int t_row = 0; t_row < target_rows; t_row++) {
			for (int t_col = 0; t_col < target_cols; t_col++) {
				if (matrix[target_y + t_row][target_x + t_col] == 1) {
					return false;
				}

				else {
					return true;
				}
			}
		}
	}

	return true;
}

bool AMapGenerator::checkvisited(TArray<TArray<int>>& matrix, TArray<TArray<int>>& target, int target_y, int target_x) {
	int matrix_rows = matrix.Num();
	int matrix_cols = matrix[0].Num();
	int target_rows = target.Num();
	int target_cols = target[0].Num();

	if (target_y + target_rows >= matrix_rows || target_x + target_cols >= matrix_cols || target_x < 0 || target_y < 0) {
		return false;
	}

	else {
		for (int t_row = 0; t_row < target_rows; t_row++) {
			for (int t_col = 0; t_col < target_cols; t_col++) {
				if (matrix[target_y + t_row][target_x + t_col] == 1) {
					return false;
				}

				else {
					return true;
				}
			}
		}
	}

	return true;
}

void AMapGenerator::checkWall(TArray<TArray<int>>& matrix, TArray<int>& loc, TArray<TArray<int>>& rot) {
	int rows = matrix.Num();
	int cols = matrix[0].Num();

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			if (matrix[r][c] == 1) {
				TArray<int> adjElements = adjCheck(matrix, r, c);
				if (adjElements[1] == 2) { //If space on left == 2
					int loc_x = ((c + 1) * cell_size) - 1;
					int loc_y = ((r + 1) * cell_size) - 1;
					//UE_LOG(LogTemp, Warning, TEXT("X : %s"), *(FString::FromInt(loc_x)));
					//UE_LOG(LogTemp, Warning, TEXT("Y : %s"), *(FString::FromInt(loc_y)));
					loc.Add(loc_x);
					loc.Add(loc_y);
				}
			}
		}
	}

}

TArray<int> AMapGenerator::GetScale(int target_dimX, int target_dimY)
{
	TArray<int> testArr;
	testArr.Add(0);
	testArr.Add(1);
	return testArr;
}

void AMapGenerator::spawnWall(const FVector& Location)
{
	
	AStaticMeshActor* MyNewActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass());
	MyNewActor->SetMobility(EComponentMobility::Stationary);
	MyNewActor->SetActorLocation(Location);
	UStaticMeshComponent* MeshComponent = MyNewActor->GetStaticMeshComponent();
	MeshComponent->SetStaticMesh(wall);
	//static ConstructorHelpers::FObjectFinder<UStaticMesh>Asset(TEXT("StaticMesh'/Game/Models/Test_Block.Test_Block'"));
	//MeshComponent->SetStaticMesh(Asset.Object);
	
	
}

void AMapGenerator::spawnFloor()
{
	FVector ActorLocation = FVector(0.f, 0.f, 0.f);
	AStaticMeshActor* MyNewActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass());
	MyNewActor->SetMobility(EComponentMobility::Stationary);
	MyNewActor->SetActorLocation(ActorLocation);
	UStaticMeshComponent* MeshComponent = MyNewActor->GetStaticMeshComponent();
	MeshComponent->SetStaticMesh(floor);
	TArray<int> targetDim = { (400 * 3 * 3), (400 * 3 * 3), 100 };
	scaleObject(MyNewActor, floorDim, targetDim);
}

void AMapGenerator::scaleObject(AStaticMeshActor* actor, TArray<int>& dimensions, TArray<int>& targetDim)
{
	int dimX = dimensions[0];
	int dimY = dimensions[1];
	int dimZ = dimensions[2];
	FString print = FString::FromInt(dimX);
	UE_LOG(LogTemp, Warning, TEXT("X dimension is : %s"), *print);

	int tarDimX = targetDim[0];
	int tarDimY = targetDim[1];
	int tarDimZ = targetDim[2];
	FString print2 = FString::FromInt(tarDimX);
	UE_LOG(LogTemp, Warning, TEXT("target X dimension is : %s"), *print2);

	FVector oriScale = actor->GetActorScale3D();
	FVector scaleVec = FVector(float(tarDimX / dimX), float(tarDimY / dimY), float(tarDimZ / dimZ));

	actor->SetActorScale3D(scaleVec);
}

void AMapGenerator::InstantiateMatrix(TArray<TArray<int>>& matrix, int rows, int cols, int c_size)
{

	for (int y = 0; y < rows * c_size; y++) {
		TArray<int> matrix_y;
		for (int x = 0; x < cols * c_size; x++) {
			matrix_y.Add(0);
		}

		matrix.Add(matrix_y);

	}

	//FString testprint = FString::FromInt(rows * c_size);
	//UE_LOG(LogTemp, Warning, TEXT("size of m_id is: %s"), *testprint);

}

TArray<TArray<int>> AMapGenerator::CreateVoid() {
	int dir = rand() % 2; //0 horizontal, 1 vertical
	int scale = ((rand() % 5) + 1) * 4;
	TArray<TArray<int>> r_id;
	if (dir == 0) {
		for (int r = 0; r < scale; r++) {
			TArray<int> r_idc;
			for (int c = 0; c < 2; c++) {
				r_idc.Add(0);
			}
			r_id.Add(r_idc);
		}
	}

	else {
		for (int r = 0; r < 2; r++) {
			TArray<int> r_idc;
			for (int c = 0; c < scale; c++) {
				r_idc.Add(0);
			}
			r_id.Add(r_idc);
		}
	}

	return r_id;
}

void AMapGenerator::FixRoom(TArray<TArray<int>>& matrix) {
	int rows = matrix.Num();
	int cols = matrix[0].Num();
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			if (matrix[r][c] == 0) {
				TArray<int> adjElements = adjCheck(matrix, r, c);
				if (adjElements.Contains(2)) {
					matrix[r][c] = 1;
				}
			}

		}
	}
}

void AMapGenerator::PopulateRooms(TMap<int, TArray<TArray<int>>>& Room_Prop, TArray<TArray<int>>& matrix, int rows, int cols, int c_size) {
	TArray<TArray<int>> r_id;
	for (int r = 0; r < c_size; r++) {
		TArray<int> r_idx;
		for (int c = 0; c < c_size; c++) {
			if (c == 0 || r == 0 || c == c_size - 1 || r == c_size - 1) {
				r_idx.Add(1);
			}

			else {
				r_idx.Add(2);
			}
		}
		r_id.Add(r_idx);
	}

	int room_num = 0;

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			TArray<TArray<int>> room_shape;
			room_num++;
			for (int y = 0; y < c_size; y++) {
				TArray<int> room_shape_y;
				for (int x = 0; x < c_size; x++) {
					//matrix[(r * c_size) + y][(c * c_size) + x] = r_id[y][x];
					room_shape_y.Add(r_id[y][x]);
				}
				room_shape.Add(room_shape_y);
			}
			Room_Prop.Add(room_num, room_shape);
		}
	}
}

void AMapGenerator::PrintMatrix(TArray<TArray<int>>& matrix) {
	int rows = matrix.Num();
	int cols = matrix[0].Num();
	FString print = "Matrix is \n";

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			print += " ";
			print += FString::FromInt(matrix[r][c]);
		}

		print += "\n";
	}

	UE_LOG(LogTemp, Warning, TEXT("%s"), *print);
}

void AMapGenerator::PrintMapInfo(TMap<int, TArray<TArray<int>>>& Room_Prop) {
	int num_rooms = Room_Prop.Num();
	FString print = "The map has" + FString::FromInt(num_rooms) + "rooms \n";
	int room_count = 0;

	for (auto& It : Room_Prop) {
		room_count++;
		print += "Room Number " + FString::FromInt(room_count) + "\n";
		int row = (It.Value).Num();
		int cols = (It.Value)[0].Num();
		for (int r = 0; r < row; r++) {
			for (int c = 0; c < cols; c++) {
				print += FString::FromInt(It.Value[r][c]) + " ";
			}
			print += "\n";
		}
		print += "\n";
	}

	UE_LOG(LogTemp, Warning, TEXT("%s"), *print);
}

void AMapGenerator::UpdateMatrix(TMap<int, TArray<TArray<int>>>& Room_Prop, TArray<TArray<int>>& matrix)
{

	TArray<TArray<TArray<int>>> roomArray;
	for (auto& It : Room_Prop) {
		roomArray.Add(It.Value);
	}

	FString print = "Updating Matrix \n";

	//Update spatial identities
	for (int y = 0; y < y_ax; y++) {
		for (int r = 0; r < cell_size; r++) {
			for (int x = 0; x < x_ax; x++) {
				for (int c = 0; c < cell_size; c++) {
					matrix[(y * cell_size) + r][(x * cell_size) + c] = roomArray[(y * x) + x][r][c];

				}
			}
		}
	}
}

void AMapGenerator::UpdateRooms_FromMatrix(TMap<int, TArray<TArray<int>>>& Room_Prop, TArray<TArray<int>>& matrix)
{
	TArray<TArray<TArray<int>>> roomArray;
	for (auto& It : Room_Prop) {
		roomArray.Add(It.Value);
	}

	for (int y = 0; y < y_ax; y++) {
		for (int x = 0; x < x_ax; x++) {
			for (int r = 0; r < cell_size; r++) {
				for (int c = 0; c < cell_size; c++) {
					roomArray[(y * x) + x][r][c] = matrix[(y * cell_size) + r][(x * cell_size) + c];
				}
			}
		}
	}

	int count = 0;

	for (auto& It : Room_Prop) {
		It.Value = roomArray[count];
	}
}

void AMapGenerator::AddDoors(TMap<int, TArray<TArray<int>>>& Room_Prop, TArray<TArray<int>>& matrix)
{

	//Change doors for rows
	for (int y = 1; y < y_ax; y++) {

		for (int x = 0; x < x_ax; x++) {
			TArray<int> x_Arr;
			for (int c = 1; c < cell_size; c++) {
				if (matrix[(y * cell_size) - 2][(x * cell_size) + c] == 2 && matrix[(y * cell_size) - 2][(x * cell_size) + c + 1] == 2 &&
					matrix[(y * cell_size) + 1][(x * cell_size) + c] == 2 && matrix[(y * cell_size) + 1][(x * cell_size) + c + 1] == 2) {
					x_Arr.Add(c);
				}
			}

			if (x_Arr.Num() == 0) {

			}

			else {
				//FString testprint = FString::FromInt(x_Arr.Num());
				//UE_LOG(LogTemp, Warning, TEXT("x_Arr is : %s"), *testprint);
				int rand_xind = rand() % (x_Arr.Num());
				int rand_x = x_Arr[rand_xind];
				matrix[y * cell_size][(x * cell_size) + rand_x] = 3;
				matrix[y * cell_size][(x * cell_size) + rand_x + 1] = 3;
				matrix[y * cell_size - 1][(x * cell_size) + rand_x] = 3;
				matrix[y * cell_size - 1][(x * cell_size) + rand_x + 1] = 3;
			}

		}
	}
	//Change doors for cols
	for (int y = 0; y < y_ax; y++) {

		for (int x = 1; x < x_ax; x++) {
			TArray<int> y_Arr;
			for (int r = 1; r < cell_size; r++) {
				if (matrix[(y * cell_size) + r][(x * cell_size) - 2] == 2 && matrix[(y * cell_size) + r][(x * cell_size) + 1] == 2 &&
					matrix[(y * cell_size) + r + 1][(x * cell_size) - 2] == 2 && matrix[(y * cell_size) + r + 1][(x * cell_size) + 1] == 2) {
					y_Arr.Add(r);
				}
			}

			if (y_Arr.Num() == 0) {

			}

			else {
				FString testprint = FString::FromInt(y_Arr.Num());
				UE_LOG(LogTemp, Warning, TEXT("x_Arr is : %s"), *testprint);
				int rand_yind = rand() % (y_Arr.Num());
				int rand_y = y_Arr[rand_yind];
				matrix[(y * cell_size) + rand_y][(x * cell_size)] = 3;
				matrix[(y * cell_size) + rand_y][(x * cell_size) - 1] = 3;
				matrix[(y * cell_size) + rand_y + 1][(x * cell_size)] = 3;
				matrix[(y * cell_size) + rand_y + 1][(x * cell_size) - 1] = 3;
			}


		}
	}
}

void AMapGenerator::MapRemove(TMap<int, TArray<TArray<int>>>& Room_Prop, int itr) {
	for (auto& It : Room_Prop) {
		TArray<TArray<int>> Room = It.Value;
		RemoveSpace(Room, itr);
		It.Value = Room;
	}

}

void AMapGenerator::RemoveSpace(TArray<TArray<int>>& matrix, int itr) {
	int rows = matrix.Num();
	int cols = matrix[0].Num();

	TArray<TArray<int>> visited;
	for (int r = 0; r < rows; r++) {
		TArray<int> visited_x;
		for (int c = 0; c < cols; c++) {
			visited_x.Add(0);
		}
		visited.Add(visited_x);
	}

	int count = 0;
	int failsafe = 0;

	while (count < itr) {

		int yes_no = rand() % 5;
		if (yes_no > 0) {
			TArray<TArray<int>> removeMe = CreateVoid();
			int randCol = rand() % cols;
			int randRow = rand() % rows;
			bool pass = checkvalid(visited, removeMe, randRow, randCol);

			if (pass == true) {
				//UE_LOG(LogTemp, Warning, TEXT("pass"));
				for (int r = 0; r < removeMe.Num(); r++) {
					for (int c = 0; c < removeMe[0].Num(); c++) {
						matrix[randRow + r][randCol + c] = removeMe[r][c];
						visited[randRow + r][randCol + c] = 1;
					}
				}
				count++;
				failsafe++;

			}
			else {
				//UE_LOG(LogTemp, Warning, TEXT("fail"));
				failsafe++;
			}

		}

		else {
			//UE_LOG(LogTemp, Warning, TEXT("skip"));
			count++;
			failsafe++;
		}

	}

	FixRoom(matrix);
	//UE_LOG(LogTemp, Warning, TEXT("Specified iterations is %s"), *(FString::FromInt(itr)));
	//UE_LOG(LogTemp, Warning, TEXT("Count: %s"), *(FString::FromInt(count)));
	//PrintMatrix(matrix);

}

