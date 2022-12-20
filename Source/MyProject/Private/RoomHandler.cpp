// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomHandler.h"

#include "BaseFloor.h"
#include "Furniture.h"
#include "Engine.h"
#include "Components/BoxComponent.h"
#include "Pocket.h"

// Sets default values
ARoomHandler::ARoomHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoomHandler::BeginPlay()
{
	Super::BeginPlay();

	SpawnFloor(true);
	//SpawnFloor(false);
	
}

// Called every frame
void ARoomHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoomHandler::SpawnFloor(bool IsFirst)
{


	SpawnLocation = FVector(3000.0f, 0.0f, 0.0f);
	SpawnRotation = FRotator(0, 0, 0);
	FloorSize = FVector(2000.f, 2000.f, 10.f);




	if (!IsFirst)
	{
		ABaseFloor* LastRoom = LevelList.Last();
		SpawnLocation = LastRoom->GetSpawnLocation()->GetComponentTransform().GetTranslation();
	}

	ABaseFloor* NextRoom = nullptr;
	NextRoom = GetWorld()->SpawnActor<ABaseFloor>(TestRoom,
		SpawnLocation, SpawnRotation, SpawnInfo);



	//Get Floor Dimensions for matrix
	FloorSize = NextRoom->GetFloorMesh()->Bounds.BoxExtent;


	//Generate RandomMatrix
	RandomMatrix = ARoomHandler::GenerateRMatrix(XTiles, YTiles);

	//Test Matrix
	//TArray<int32> emptyRow;
	//TArray<int32> FullRow;
	//emptyRow.Init(0, 3);
	//FullRow.Init(1, 3);
	//RandomMatrix.Init(emptyRow, 3);
	//RandomMatrix[1] = FullRow;
	/*FVector TestOffset = 2 * FVector(0, 0, 10);
	AFurniture* TestNextPocket = nullptr;;
	TestNextPocket = GetWorld()->SpawnActor<AFurniture>(PocketObject,
		SpawnLocation + TestOffset, SpawnRotation, SpawnInfo);
	FVector TestNewScale = TestNextPocket->GetActorScale3D();
	TestNewScale = TestNewScale * FVector(float(10) / 2, float(10) / 2, 1);

	TestNextPocket->SetActorScale3D(TestNewScale);*/


	for (int i = 0; i < RandomMatrix.Num(); i++) {

		for (int j = 0; j < RandomMatrix[i].Num(); j++) {

			if (RandomMatrix[i][j] >= 100000) {
				//Strange Math to deal with some scaling issues
				FVector Offset = 2 * FVector(i * FloorSize.X / XTiles, j * FloorSize.Y / YTiles, 10);
				AFurniture* NextCirc = nullptr;;
				NextCirc = GetWorld()->SpawnActor<AFurniture>(CirculationSpace,
					SpawnLocation + Offset, SpawnRotation, SpawnInfo);
				FVector NewScale = NextCirc->GetActorScale3D();
				NewScale = NewScale * FVector(0.5f, 0.5f, 1);

				NextCirc->SetActorScale3D(NewScale);
				RandomMatrix[i][j] -= 100000;
			}//Spawn Pocket at pocket origin with scale defined by value
			if (RandomMatrix[i][j] >= 20000) {

				UE_LOG(LogTemp, Warning, TEXT("Matrix Value %f"), float(RandomMatrix[i][j]));
				int PocketWidth = (RandomMatrix[i][j] - 20000) / 100;
				int PocketHeight = (RandomMatrix[i][j] - 20000) % 100;
				int upperRange = 1;

				if (PocketWidth >= 5 && PocketHeight >= 5) {

					upperRange = 6;

				}
				else if (PocketWidth >= 2 && PocketHeight >= 2) {

					upperRange = 3;

				}

				RandomPocket = FMath::RandRange(1, upperRange);
				FVector Offset = 2 * FVector(i * FloorSize.X / XTiles, j * FloorSize.Y / YTiles, 10);
				AFurniture* NextPocket = nullptr;;

				if (RandomPocket == 1) {

					NextPocket = GetWorld()->SpawnActor<AFurniture>(PocketObject,
						SpawnLocation + Offset, SpawnRotation, SpawnInfo);
					FVector NewScale = NextPocket->GetActorScale3D();
					NewScale = NewScale * FVector(float(PocketHeight) / 2, float(PocketWidth) / 2, 1);

					NextPocket->SetActorScale3D(NewScale);

				}
				else if (RandomPocket == 2) {

					NextPocket = GetWorld()->SpawnActor<AFurniture>(PocketObject1,
						SpawnLocation + Offset, SpawnRotation, SpawnInfo);
					/*FVector NewScale = NextPocket->GetActorScale3D();
					NewScale = NewScale * FVector(float(PocketHeight) / 2, float(PocketWidth) / 2, 1);

					NextPocket->SetActorScale3D(NewScale);*/

				}
				else if (RandomPocket == 3) {

					NextPocket = GetWorld()->SpawnActor<AFurniture>(PocketObject2,
						SpawnLocation + Offset, SpawnRotation, SpawnInfo);
					/*FVector NewScale = NextPocket->GetActorScale3D();
					NewScale = NewScale * FVector(float(PocketHeight) / 2, float(PocketWidth) / 2, 1);

					NextPocket->SetActorScale3D(NewScale);*/

				}
				else if (RandomPocket == 4) {

					NextPocket = GetWorld()->SpawnActor<AFurniture>(PocketObject3,
						SpawnLocation + Offset, SpawnRotation, SpawnInfo);
					/*FVector NewScale = NextPocket->GetActorScale3D();
					NewScale = NewScale * FVector(float(PocketHeight) / 2, float(PocketWidth) / 2, 1);

					NextPocket->SetActorScale3D(NewScale);*/

				}
				else if (RandomPocket == 5) {

					NextPocket = GetWorld()->SpawnActor<AFurniture>(PocketObject4,
						SpawnLocation + Offset, SpawnRotation, SpawnInfo);
					/*FVector NewScale = NextPocket->GetActorScale3D();
					NewScale = NewScale * FVector(float(PocketHeight) / 2, float(PocketWidth) / 2, 1);

					NextPocket->SetActorScale3D(NewScale);*/

				}
				else if (RandomPocket == 6) {

					NextPocket = GetWorld()->SpawnActor<AFurniture>(PocketObject5,
						SpawnLocation + Offset, SpawnRotation, SpawnInfo);
					/*FVector NewScale = NextPocket->GetActorScale3D();
					NewScale = NewScale * FVector(float(PocketHeight) / 2, float(PocketWidth) / 2, 1);

					NextPocket->SetActorScale3D(NewScale);*/

				}
			}


		}

	}

	if (NextRoom)
	{
		if (NextRoom->GetTrigger())
		{
			NextRoom->GetTrigger()->OnComponentBeginOverlap.
				AddDynamic(this, &ARoomHandler::OnOverlapBegin);
		}
	}

	LevelList.Add(NextRoom);
	if (LevelList.Num() > 5)
	{
		LevelList.RemoveAt(0);
	}

}

void ARoomHandler::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	SpawnFloor(false);

}

TArray<TArray<int32>> ARoomHandler::GenerateRMatrix(int RoomWidth, int RoomLength)
{
	//Create empty nested TArray for eventual RMatrix. Currently 0 indicates empty space, 1 indicates circulation placeholder
	TArray<TArray<int32>> RMatrix;
	TArray<int32> emptyRow;
	emptyRow.Init(0, RoomLength);
	RMatrix.Init(emptyRow, RoomWidth);


	TSet<TArray<int32>> CirculationCoordinates;
	CirculationCoordinates = ARoomHandler::GenerateCirculation({ 0, 0 }, { RoomWidth - 1, RoomLength - 1 }, RoomWidth, RoomLength, 0);

	for (TArray<int32> Coords : CirculationCoordinates) {

		RMatrix[Coords[0]][Coords[1]] = 100000;

	}

	//Getting Empty Coordinate List for later development
	TSet<TArray<int32>> EmptyCoordinateList;


	for (int i = 0; i < RoomWidth; i++) {

		for (int j = 0; j < RoomLength; j++) {


			EmptyCoordinateList.Add({ i, j });

		}

	}

	//Get difference between full grid and circulation coordinates to get empty coordinate list
	EmptyCoordinateList = EmptyCoordinateList.Difference(CirculationCoordinates);

	TMap<int32, Pocket> PocketList = ARoomHandler::GeneratePockets(EmptyCoordinateList);
	for (TTuple<int32, Pocket> pockTuple : PocketList) {

		Pocket pock = pockTuple.Get<1>();

		//Assigning Pocket Origins here
		//Integer value of pocket given in the form 2XXYY where 2 indicates pocket, XX indicates width and YY indicates height
		if (RMatrix[pock.Origin[0]][pock.Origin[1]] <= 20000) {
			RMatrix[pock.Origin[0]][pock.Origin[1]] += 20000 + pock.width * 100 + pock.height;
		}
	}

	return RMatrix;
}

TSet<TArray<int32>> ARoomHandler::GenerateCirculation(TArray<int32> EntranceCoords, TArray<int32> ExitCoords, int RoomWidth, int RoomLength, int CirculationType)
{
	//Init set of travelled coordinates
	TSet<TArray<int32>> Trail;

	//Init Cursor variable to remember position of circulation head
	TArray<int32> Cursor = EntranceCoords;

	//Init various variables for function
	bool CirculationComplete = false; //bool to terminate circulation loop
	int lastDirection = 0; //int to remember previously travelled direction
	int loopCounter = 0; //temporary int to limit number of loop iterations during random generation
	int exitDir = 0; //int to represent position of exit relative to cursor
	TArray<int> exitRef; //Coordinates = exit - cursor
	float theta; //Angle between exit relative position and +x
	float phi; //Angle between lastDirection and +x
	float randOffset = 0; //Variable to push random range up or down to influence circulation direction
	float* pROffset = &randOffset;

	while (!CirculationComplete)
	{
		//Check for circulation before anything else
		if (Cursor == ExitCoords || loopCounter == MaxLoopCount) {
			CirculationComplete = true;
		}

		exitRef = { ExitCoords[0] - Cursor[0], ExitCoords[1] - Cursor[1] }; //make this more elegant later -.-
		//Accounting for zero division errors
		if (exitRef[0] != 0) {

			theta = atan2(exitRef[1], exitRef[0]);
			theta = theta * 180 / PI;
			theta += 180;
			//UE_LOG(LogTemp, Warning, TEXT("theta is %f"), theta);

		}
		else if (exitRef[1] != 0) {

			theta = 90 * (1 + ((exitRef[1] > 0) - (exitRef[1] < 0)));

		}
		else {

			theta = FMath::RandRange(0, 360); //Fuck this, just want to get rid of the zero division error for now

		}

		//UE_LOG(LogTemp, Warning, TEXT("theta is %f"), theta);
		phi = 90 * lastDirection;
		//Account for overrotation and make sure offset points to correct direction (should make this into a function next time)
		//randOffset = theta - phi;
		*pROffset = theta - phi;
		//int * pROffset = &randOffset;


		if (*pROffset >= 180 || *pROffset <= -180) {
			//Add 360 if less than 180, subtract 360 if more than 180
			//UE_LOG(LogTemp, Warning, TEXT("check PN randOffset is %i"), ((*pROffset > 0) - (*pROffset < 0)));
			*pROffset += (((*pROffset < 0) - (*pROffset > 0)) * 360);
		}
		//Normalize randOffset and multiply by 15 (Can modify to change "strength" of wind in the future
		if (*pROffset != 0) {

			//UE_LOG(LogTemp, Warning, TEXT("check normalization randOffset is %i"), ((*pROffset > 0) - (*pROffset < 0)));
			*pROffset = 15 * ((*pROffset > 0) - (*pROffset < 0));
			//UE_LOG(LogTemp, Warning, TEXT("check final randOffset is %i"), *pROffset);
		}

		//randOffset = ARoomHandler::OffsetCorrection(&randOffset);

		//UE_LOG(LogTemp, Warning, TEXT("randOffset is %f"), randOffset);
		//UE_LOG(LogTemp, Warning, TEXT("pROffset is %f"), *pROffset);
		loopCounter += 1;

		//bool isPreviouslyTravelledTile = Trail.Contains(Cursor);
		bool isPreviouslyTravelledTile = Trail.Contains(Cursor);

		//Check for border of the room
		if (Cursor[0] < 0 || Cursor[0] >= RoomWidth || Cursor[1] < 0 || Cursor[1] >= RoomLength) {

			int nextDir = 2;
			nextDir += lastDirection;
			if (nextDir >= 4) {
				nextDir -= 4;
			}
			if (nextDir < 0) {
				nextDir += 4;
			}
			lastDirection = nextDir;
			//Move cursor back in opposite direction
			Cursor[nextDir % 2] = Cursor[nextDir % 2] + (1 - 2 * (nextDir / 2));
			continue;

		}
		else //Check for previously travelled tiles (currently commented out cos it doesn't do anything
	   /*if (isPreviouslyTravelledTile) {
		   Trail.Add(Cursor); //Add new coords to set
		   int nextDir = FMath::RandRange(-45 + randOffset, 45 + randOffset); //Random left turn, right turn, or no change in direction of Cursor head
		   //Reduce outcome into -1, 0 or 1
		   nextDir = nextDir / 15;
		   if (nextDir != 0) {
			   nextDir = nextDir / abs(nextDir);
		   }

		   nextDir += lastDirection; //Apply turn to last direction
		   //Correct back to the 0-3 range as direction indicators
		   if (nextDir >= 4){
			   nextDir -= 4;
			   }
		   if (nextDir < 0) {
			   nextDir += 4;
		   }
		   lastDirection = nextDir;
		   //Use modulus to access coordinate index so if-else doesn't have to be used
		   Cursor[1 - nextDir % 2] = Cursor[1 - nextDir % 2] + (1-2*(nextDir/2));
	   }else */
		{

			Trail.Add(Cursor);
			int nextDir = FMath::RandRange(-45 + *pROffset, 45 + *pROffset); //Random left turn, right turn, or no change in direction of Cursor head
			//Reduce outcome into -1, 0 or 1
			nextDir = nextDir / 15;
			nextDir = (nextDir < 0) - (nextDir > 0);
			//UE_LOG(LogTemp, Warning, TEXT("nextDir is %i"), nextDir);

			nextDir += lastDirection;
			if (nextDir >= 4) {
				nextDir -= 4;
			}
			if (nextDir < 0) {
				nextDir += 4;
			}
			//UE_LOG(LogTemp, Warning, TEXT("This Step is %i"), nextDir);
			//nextDir = 1;
			lastDirection = nextDir;
			Cursor[nextDir % 2] = Cursor[nextDir % 2] + (1 - 2 * (nextDir / 2));

		}



	}

	return Trail;


}

TMap<int32, Pocket> ARoomHandler::GeneratePockets(TSet<TArray<int32>> Emptycoords)
{
	//Debugging
	UE_LOG(LogTemp, Warning, TEXT("Empty Coordinates are: "));
	for (TArray<int32> coords : Emptycoords) {

		UE_LOG(LogTemp, Warning, TEXT("( %i, %i)"), coords[0], coords[1]);

	}

	//Create array to remember Pockets
	TMap<int32, Pocket> PocketList;
	TMap<int32, Pocket> AltPocketList;
	Pocket currentPock = Pocket(0, 0, { 0, 0 });
	int PocketIndex = 0;
	//For every row, look for areas of consecutive numbers and check if previous pockets should be heightened
	for (int row = 0; row < YTiles; row++) {

		//bool to mark start of new pocket being created
		bool stillBuilding = false;
		for (int column = 0; column < XTiles; column++) {


			if (!stillBuilding) {

				//Set new origin
				currentPock = Pocket(0, 0, { row, column });

				//currentPock.height = 1;


			}
			if (Emptycoords.Contains({ row, column })) {
				//Widen current pocket by 1 tile
				currentPock.AddCol(1);
				stillBuilding = true;
			}
			else
			{
				if (stillBuilding) {
					//If current pocket stops being consecutive, add current pocket to the pocket list
					currentPock.AddRow(1);
					PocketList.Add(PocketIndex, currentPock);
					PocketIndex += 1;

					//Account for previous pockets
					for (TTuple<int32, Pocket> previousPocket : PocketList) {
						Pocket PreviousPocket = previousPocket.Get<1>();
						Pocket* p_PreviousPocket = &previousPocket.Get<1>();
						if (currentPock.CheckStacking(*p_PreviousPocket)) {
							//Add height to every pocket that is stacked below current pocket if pockets line up within new pocket range
							if (((*p_PreviousPocket).Origin[1] >= currentPock.Origin[1]) &&
								((*p_PreviousPocket).Origin[1] + (*p_PreviousPocket).width
									<= currentPock.Origin[1] + currentPock.width)) {
								UE_LOG(LogTemp, Warning, TEXT("Old Pocket Grew"));
								PreviousPocket.AddRow(1);
								AltPocketList.Add(previousPocket.Get<0>(), PreviousPocket);

							}
							else {
								//Create a new pocket that represents the smallest square within the new expanded space
								//(Hate this part, should improve it later)
								//Width is smallest right side value subtracted by largest left side value
								UE_LOG(LogTemp, Warning, TEXT("Old Pocket Grew, width shrunk"));
								int ExtraPocketWidth = std::min((*p_PreviousPocket).Origin[1] + (*p_PreviousPocket).width,
									currentPock.Origin[1] + currentPock.width) -
									std::max((*p_PreviousPocket).Origin[1], currentPock.Origin[1]);
								//height is previous pocket +1
								PreviousPocket.AddRow(1);
								//New Origin Location is largest left side value
								int NewOriginX = std::max((*p_PreviousPocket).Origin[1], currentPock.Origin[1]);
								PreviousPocket.width = ExtraPocketWidth;
								PreviousPocket.Origin[1] = NewOriginX;
								//(*p_PreviousPocket).Origin[0] = std::max((*p_PreviousPocket).Origin[0], currentPock.Origin[0]);
								AltPocketList.Add(PocketIndex, PreviousPocket);
								PocketIndex += 1;

							}
							/*UE_LOG(LogTemp, Warning, TEXT("PocketHeight is %i"), previousPocket.height);
							UE_LOG(LogTemp, Warning, TEXT("PocketWidth is %i"), previousPocket.width);
							UE_LOG(LogTemp, Warning, TEXT("PocketSize is %i"), previousPocket.Size());
							UE_LOG(LogTemp, Warning, TEXT("PocketIndex is %i"), previousPocket.Get<0>());*/
						}

					}
				}

				//Reset stillBuilding bool and dump new Pockets from AltPocketList into PocketList
				PocketList.Append(AltPocketList);
				stillBuilding = false;

			}


		}
		//End of the row
		if (currentPock.width != 0 && currentPock.height != 1) {
			currentPock.AddRow(1);
			PocketList.Add(PocketIndex, currentPock);
			PocketIndex += 1;

			//Account for previous pockets
			for (TTuple<int32, Pocket> previousPocket : PocketList) {
				Pocket PreviousPocket = previousPocket.Get<1>();
				Pocket* p_PreviousPocket = &previousPocket.Get<1>();
				if (currentPock.CheckStacking(*p_PreviousPocket)) {
					//Add height to every pocket that is stacked below current pocket if pockets line up within new pocket range
					if (((*p_PreviousPocket).Origin[1] >= currentPock.Origin[1]) &&
						((*p_PreviousPocket).Origin[1] + (*p_PreviousPocket).width <= currentPock.Origin[1] + currentPock.width)) {
						UE_LOG(LogTemp, Warning, TEXT("Old Pocket Grew"));
						PreviousPocket.AddRow(1);
						AltPocketList.Add(previousPocket.Get<0>(), PreviousPocket);

					}
					else {
						//Create a new pocket that represents the smallest square within the new expanded space
						//(Hate this part, should improve it later)
						//Width is smallest right side value subtracted by largest left side value
						UE_LOG(LogTemp, Warning, TEXT("Old Pocket Grew, width shrunk"));
						int ExtraPocketWidth = std::min((*p_PreviousPocket).Origin[1] + (*p_PreviousPocket).width,
							currentPock.Origin[1] + currentPock.width) -
							std::max((*p_PreviousPocket).Origin[1], currentPock.Origin[1]);
						//height is previous pocket +1
						PreviousPocket.AddRow(1);
						//New Origin Location is largest left side value
						int NewOriginX = std::max((*p_PreviousPocket).Origin[1], currentPock.Origin[1]);
						PreviousPocket.width = ExtraPocketWidth;
						PreviousPocket.Origin[1] = NewOriginX;
						//(*p_PreviousPocket).Origin[0] = std::max((*p_PreviousPocket).Origin[0], currentPock.Origin[0]);
						AltPocketList.Add(PocketIndex, PreviousPocket);
						PocketIndex += 1;

					}
				}


			}

			PocketList.Append(AltPocketList);

		}

	}
	//Remove subrectangles first 
	/*for (TTuple<int32, Pocket> PocketTuple : PocketList) {

		UE_LOG(LogTemp, Warning, TEXT("Main Pocket %i has width %i and height %i at Origin (%i, %i)"),
			PocketTuple.Get<0>(), PocketTuple.Get<1>().width, PocketTuple.Get<1>().height, PocketTuple.Get<1>().Origin[0],
			PocketTuple.Get<1>().Origin[1]);
		//Remove subrectangles first
		for (TTuple<int32, Pocket> p_otherPockTuple : PocketList) {
			Pocket mainPocket = PocketTuple.Get<1>();
			Pocket otherPock = p_otherPockTuple.Get<1>();
			//Remove subrectangles, don't compare pockets with themselves
			if (otherPock.IsSubRect(mainPocket) && (PocketTuple.Get<0>() != p_otherPockTuple.Get<0>())) {

				UE_LOG(LogTemp, Warning, TEXT("Removing pocket %i of width %i and height %i at Origin (%i, %i)"),
					p_otherPockTuple.Get<0>(), p_otherPockTuple.Get<1>().width, p_otherPockTuple.Get<1>().height, p_otherPockTuple.Get<1>().Origin[0],
					p_otherPockTuple.Get<1>().Origin[1]);
				PocketList.Remove(p_otherPockTuple.Get<0>());

			}

		}

	}*/
	ARoomHandler::RemoveSubrectangles(PocketList);

	//Then subtract overlaps from smaller pockets
	for (TTuple<int32, Pocket> PocketTuple : PocketList) {

		UE_LOG(LogTemp, Warning, TEXT("Main Pocket %i has width %i and height %i at Origin (%i, %i)"),
			PocketTuple.Get<0>(), PocketTuple.Get<1>().width, PocketTuple.Get<1>().height, PocketTuple.Get<1>().Origin[0],
			PocketTuple.Get<1>().Origin[1]);

		for (TTuple<int32, Pocket> p_otherPockTuple : PocketList) {
			Pocket mainPocket = PocketTuple.Get<1>();
			Pocket otherPock = p_otherPockTuple.Get<1>();
			//Check if mainPocket is larger and more square, don't compare pockets with themselves
			if (mainPocket.CheckOverlap(otherPock) &&
				(PocketTuple.Get<0>() != p_otherPockTuple.Get<0>()) &&
				(mainPocket.Size() > otherPock.Size() ||
					(mainPocket.Size() == otherPock.Size() && mainPocket.SquareScore() < otherPock.SquareScore()))
				) {

				UE_LOG(LogTemp, Warning, TEXT("Removing pocket %i of width %i and height %i at Origin (%i, %i)"),
					p_otherPockTuple.Get<0>(), p_otherPockTuple.Get<1>().width, p_otherPockTuple.Get<1>().height, p_otherPockTuple.Get<1>().Origin[0],
					p_otherPockTuple.Get<1>().Origin[1]);

				PocketList.Remove(p_otherPockTuple.Get<0>());


			}

		}

	}


	//Debugging
	for (TTuple<int32, Pocket> PocketTuple : PocketList) {

		UE_LOG(LogTemp, Warning, TEXT("Pocket %i has width %i and height %i at Origin (%i, %i)"),
			PocketTuple.Get<0>(), PocketTuple.Get<1>().width, PocketTuple.Get<1>().height, PocketTuple.Get<1>().Origin[0],
			PocketTuple.Get<1>().Origin[1]);

	}


	return PocketList;

}

void ARoomHandler::RemoveSubrectangles(TMap<int32, Pocket> PocketList)
{

	for (TTuple<int32, Pocket> PocketTuple : PocketList) {

		UE_LOG(LogTemp, Warning, TEXT("Main Pocket %i has width %i and height %i at Origin (%i, %i)"),
			PocketTuple.Get<0>(), PocketTuple.Get<1>().width, PocketTuple.Get<1>().height, PocketTuple.Get<1>().Origin[0],
			PocketTuple.Get<1>().Origin[1]);
		//Remove subrectangles first
		for (TTuple<int32, Pocket> p_otherPockTuple : PocketList) {
			Pocket mainPocket = PocketTuple.Get<1>();
			Pocket otherPock = p_otherPockTuple.Get<1>();
			//Remove subrectangles, don't compare pockets with themselves
			if (otherPock.IsSubRect(mainPocket) && (PocketTuple.Get<0>() != p_otherPockTuple.Get<0>())) {

				UE_LOG(LogTemp, Warning, TEXT("Removing pocket %i of width %i and height %i at Origin (%i, %i)"),
					p_otherPockTuple.Get<0>(), p_otherPockTuple.Get<1>().width, p_otherPockTuple.Get<1>().height, p_otherPockTuple.Get<1>().Origin[0],
					p_otherPockTuple.Get<1>().Origin[1]);
				PocketList.Remove(p_otherPockTuple.Get<0>());

			}

		}

	}


}

int ARoomHandler::OffsetCorrection(float* offset)
{

	if (*offset >= 180 || *offset <= -180) {
		//Add 360 if less than 180, subtract 360 if more than 180
		*offset += (((*offset < 0) - (*offset > 0)) * 360);
		//Normalize randOffset and multiply by 15 (Can modify to change "strength" of wind in the future)		
		*offset = 15 * ((*offset > 0) - (*offset < 0));
		return *offset;
	}

	return 0;

}

