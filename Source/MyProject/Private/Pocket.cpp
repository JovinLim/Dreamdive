// Fill out your copyright notice in the Description page of Project Settings.


#include "Pocket.h"


Pocket::Pocket(int x = 0 , int y = 0, TArray<int32> o = { 0, 0 })
{

	width = x;
	height = y;
	Origin = o;
	size = x * y;

}

Pocket::~Pocket()
{
}

int Pocket::Size()
{

	size = width * height;
	return size;

}

void Pocket::AddRow(int y)
{

	height += y;
	return;

}

void Pocket::AddCol(int x)
{

	width += x;
	return;

}

bool Pocket::CheckOverlap(const Pocket otherPocket)
{

	bool withinX = (Origin[1] + width - otherPocket.Origin[1] >= 0 && otherPocket.Origin[1] + otherPocket.width - Origin[1] >= 0);
	bool withinY = (Origin[0] + height - otherPocket.Origin[0] >= 0 && otherPocket.Origin[0] + otherPocket.height - Origin[0] >= 0);

	return (withinX && withinY);
}

bool Pocket::CheckStacking(Pocket otherPocket)
{

	bool withinX = ((Origin[1] + width - otherPocket.Origin[1] >= 0) && (otherPocket.Origin[1] + otherPocket.width - Origin[1] >= 0));
	bool withinY = (Origin[0] == otherPocket.Origin[0] + otherPocket.height);
	UE_LOG(LogTemp, Warning, TEXT("Stacking occurred"));

	return (withinX && withinY);

}

bool Pocket::IsSubRect(Pocket otherPocket)
{
	//Check Horizontal Rectangles
	if (Origin[1] == otherPocket.Origin[1]) {
		bool withinY = (Origin[0] < otherPocket.Origin[0] + otherPocket.height && Origin[0] > otherPocket.Origin[0]);
		bool smallerWidth = (width == otherPocket.width);
		UE_LOG(LogTemp, Warning, TEXT("Horizontal Subrectangle found"));
		return(withinY && smallerWidth);
	}
	//Check Vertical Rectangles
	if (Origin[0] == otherPocket.Origin[0]) {
		bool withinX = (Origin[1] < otherPocket.Origin[1] + otherPocket.width && Origin[1] > otherPocket.Origin[1]);
		bool smallerHeight = (height == otherPocket.height);
		UE_LOG(LogTemp, Warning, TEXT("Vertical Subrectangle found"));
		return(withinX && smallerHeight);
	}
	UE_LOG(LogTemp, Warning, TEXT("Not a Subrectangle"));
	return false;
}

float Pocket::SquareScore()
{
	return abs(width/height -1.f);
}