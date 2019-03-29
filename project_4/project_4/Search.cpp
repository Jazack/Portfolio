// This project was written by Benjamin Jones without taking code from others,
// with exception of Timer.h and Timer.cpp which were given by the instructor, which was project_4.cpp
// date: 2/3/2018
#include "stdafx.h"
#include "Search.h"


Search::Search()
{
}

Search::Search(const int SIZE)
{
	myInts = new int[SIZE];
	size = SIZE;
}

bool Search::SequentialSearch(const int target)
{
	for (size_t i = 0; i < size; i++)
	{
		if (myInts[i] == target)
		{
			return true;
		}
	}
	return false;
}

bool Search::RecursiveSearch(const int target)
{
	return RecursiveSearchHelper(target, 0, size, size);
}

bool Search::RecursiveSearchHelper(const int target, int low, int high, int count)
{
	if (high >= low)
	{
		count = (count -1) / HALF;
		int place = low + count;
		if (myInts[place] == target)
		{
			return true;
		}
		else if (myInts[place] > target)
		{
			return RecursiveSearchHelper(target, low, place - 1, count + 1);
		}
		else if (myInts[place] < target)
		{
			return RecursiveSearchHelper(target, place + 1, high, count + 1);
		}
		else if (high == low)
		{
			return 0;
		}
	}
	return false;
}

bool Search::IterativeBinarySearch(const int target)
{
	int low = 0;
	int high = size;
	int place;
	int count = size;
	do
	{
		if (high >= low)
		{
			count = (count - 1) / HALF;
			place = low + count;
			if (myInts[place] == target)
			{
				return true;
			}
			else if (myInts[place] > target)
			{
				high = place - 1;
				count++;
			}
			else if (myInts[place] < target)
			{
				low = place + 1;
				count++;
			}
		
		}
		else
		{
			return false;
		}
	} while (high >= low);
	return false;
}

void Search::InitSortedArray()
{
	srand(0);
	*myInts = rand() % 5;
	for (size_t i = 1; i < size; i++)
	{
		myInts[i] = myInts[i - 1] + rand() % 5;
	}

}


Search::~Search()
{
	delete[] myInts;
}
