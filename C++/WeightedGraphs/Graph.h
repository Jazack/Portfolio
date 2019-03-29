/*
I, Benjamin Jones, certify that I wrote all of the code presented here
on my own, with exception of the code given to us from the instructor
4/20/2018
*/

#pragma once
#include <string.h>
#include<string>
#include "stdafx.h"
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

class Graph
{
public:
	Graph();
	~Graph();
	void AddEdge(string source, string target, int weight);
	void AddVertex(string lable);
	bool IsEdge(int sourceIndex, int targetIndex);
	int GetWeight(int sourceIndex, int targetIndex);
	void BreadthFirstSearch(string startingVertex);
	void DijkstraShortedPath(string startingVertex);
	void PrintGraph();

private:
	static const int MAX = 6;
	const int INFINITE = 9999;

	vector<string> myChars;
	
	int myInts[MAX][MAX];

	
};

