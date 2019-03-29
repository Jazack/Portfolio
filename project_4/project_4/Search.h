// This project was written by Benjamin Jones without taking code from others,
// with exception of Timer.h and Timer.cpp which were given by the instructor, which was project_4.cpp
// date: 2/3/2018

#pragma once
#include <stdlib.h>
#include <iostream>
using namespace std;
class Search
{
public:
	Search();
	Search(const int SIZE);
	bool SequentialSearch(const int target);
	bool RecursiveSearch(const int target);
	bool RecursiveSearchHelper(const int target, int low, int high, int count);
	bool IterativeBinarySearch(const int target);
	void InitSortedArray();
	~Search();

private:
	static const int HALF = 2;
	int *myInts;
	int size;

};

