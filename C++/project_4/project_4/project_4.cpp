// This project was written by Benjamin Jones without taking code from others,
// with exception of Timer.h and Timer.cpp which were given by the instructor, which was project_4.cpp
// date: 2/3/2018

#include "stdafx.h"
#include <iostream>
#include "Timer.h"
#include "Search.h"

#include <chrono>

using namespace std;

int main()
{
	int trueFalse;
	int time;
	const int MILLION = 1000000;
	const int FIRST_SEARCH = 3;
	const int SECOND_SEARCH = 505000;
	const int THIRD_SEARCH = 999999;
	Search mySearch = Search(MILLION);
	Timer myTime = Timer();
	cout << "Creating a sorted array of 1000000" << endl;
	mySearch.InitSortedArray();
	cout << "Finished creating a sorted array of 1000000" << endl << endl;

	cout << "Searching for a number at the start of the array" << endl;
	// sequential search
	myTime.Start();
	trueFalse = mySearch.SequentialSearch(FIRST_SEARCH);
	myTime.End();
	time = myTime.DurationInNanoSeconds();
	if (trueFalse == true)
	{
		cout << "        s.SequentialSearch() returned 1 in " << time << "ns" << endl;
	}
	else
	{
		cout << "        s.SequentialSearch() returned 0 in " << time << "ns" << endl;
	}
	// recursive search
	myTime.Start();
	trueFalse = mySearch.RecursiveSearch(FIRST_SEARCH);
	myTime.End();
	time = myTime.DurationInNanoSeconds();
	if (trueFalse == true)
	{
		cout << "        s.RecursiveSearch() returned 1 in " << time << "ns" << endl;
	}
	else
	{
		cout << "        s.RecursiveSearch() returned 0 in " << time << "ns" << endl;
	}
	// binary search
	myTime.Start();
	trueFalse = mySearch.IterativeBinarySearch(FIRST_SEARCH);
	myTime.End();
	time = myTime.DurationInNanoSeconds();
	if (trueFalse == true)
	{
		cout << "        s.IterativeBinarySearch() returned 1 in " << time << "ns" << endl;
	}
	else
	{
		cout << "        s.IterativeBinarySearch() returned 0 in " << time << "ns" << endl;
	}

	cout << endl;
	// SECOND SEARCH
	cout << "Searching for a number at the middle of the array" << endl;
	// sequential search
	myTime.Start();
	trueFalse = mySearch.SequentialSearch(SECOND_SEARCH);
	myTime.End();
	time = myTime.DurationInNanoSeconds();
	if (trueFalse == true)
	{
		cout << "        s.SequentialSearch() returned 1 in " << time << "ns" << endl;
	}
	else
	{
		cout << "        s.SequentialSearch() returned 0 in " << time << "ns" << endl;
	}
	// recursive search
	myTime.Start();
	trueFalse = mySearch.RecursiveSearch(SECOND_SEARCH);
	myTime.End();
	time = myTime.DurationInNanoSeconds();
	if (trueFalse == true)
	{
		cout << "        s.RecursiveSearch() returned 1 in " << time << "ns" << endl;
	}
	else
	{
		cout << "        s.RecursiveSearch() returned 0 in " << time << "ns" << endl;
	}
	// binary search
	myTime.Start();
	trueFalse = mySearch.IterativeBinarySearch(SECOND_SEARCH);
	myTime.End();
	time = myTime.DurationInNanoSeconds();
	if (trueFalse == true)
	{
		cout << "        s.IterativeBinarySearch() returned 1 in " << time << "ns" << endl;
	}
	else
	{
		cout << "        s.IterativeBinarySearch() returned 0 in " << time << "ns" << endl;
	}
	
	cout << endl;

	// THIRD SEARCH
	cout << "Searching for a number at the middle of the array" << endl;
	// sequential search
	myTime.Start();
	trueFalse = mySearch.SequentialSearch(THIRD_SEARCH);
	myTime.End();
	time = myTime.DurationInNanoSeconds();
	if (trueFalse == true)
	{
		cout << "        s.SequentialSearch() returned 1 in " << time << "ns" << endl;
	}
	else
	{
		cout << "        s.SequentialSearch() returned 0 in " << time << "ns" << endl;
	}
	// recursive search
	myTime.Start();
	trueFalse = mySearch.RecursiveSearch(THIRD_SEARCH);
	myTime.End();
	time = myTime.DurationInNanoSeconds();
	if (trueFalse == true)
	{
		cout << "        s.RecursiveSearch() returned 1 in " << time << "ns" << endl;
	}
	else
	{
		cout << "        s.RecursiveSearch() returned 0 in " << time << "ns" << endl;
	}
	// binary search
	myTime.Start();
	trueFalse = mySearch.IterativeBinarySearch(THIRD_SEARCH);
	myTime.End();
	time = myTime.DurationInNanoSeconds();
	if (trueFalse == true)
	{
		cout << "        s.IterativeBinarySearch() returned 1 in " << time << "ns" << endl;
	}
	else
	{
		cout << "        s.IterativeBinarySearch() returned 0 in " << time << "ns" << endl;
	}
	cout << endl << "Press the [Enter] key to quit...";
	getchar();

	return 0;
}

