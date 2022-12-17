// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class CPLUSPLUS_PROJECT_API Pocket
{
public:

	int width;
	int height;
	TArray<int32> Origin;
	int size; 

	Pocket(int x, int y, TArray<int32> o);
	~Pocket();

public:

	int Size();
	//Functions to change size of pocket
	void AddRow(int y);
	void AddCol(int x);
	//Function to check if pocket is overlapping with another
	bool CheckOverlap(const Pocket otherPocket);
	//Function to check if pocket is sitting directly on top of another pocket
	bool CheckStacking(Pocket otherPocket);
	//Function to check if pocket is SubRectangle of another pocket
	bool IsSubRect(Pocket otherPocket);
	//Function to return a value that's a measure of how "square-like" the pocket is
	float SquareScore();



};
