/*
I, Benjamin Jones, certify that I wrote all of the code presented here
on my own, with exception of the code given to us from the instructor, WeightedGraphs.cpp
4/20/2018
*/

#include "stdafx.h"
#include "Graph.h"

// initializer
Graph::Graph()
{
	for (size_t i = 0; i < MAX; i++)
	{
		for (size_t j = 0; j < MAX; j++)
		{
			myInts[j][i] = -1;
		}
	}
}

// destructor
Graph::~Graph()
{
}

// function to add an edge
void Graph::AddEdge(string  source, string target, int weight)
{
	int src = -1;
	int tar = -1;
	for (size_t i = 0; i < myChars.size(); i++)
	{
		if (source == myChars.at(i))
		{
			src = i;
		}
		if (target == myChars.at(i))
		{
			tar = i;
		}
	}
	if (src != -1 && tar != -1)
	{
		myInts[src][tar] = weight;
	}
}

// function to add a vertex
void Graph::AddVertex(string lable)
{
	myChars.push_back(lable);
}

// function to determine if the part is an edge
bool Graph::IsEdge(int sourceIndex, int targetIndex)
{
	if (myInts[sourceIndex][targetIndex] > -1)
	{
		return true;
	}
	return false;
}

// gets the weight of the target
int Graph::GetWeight(int sourceIndex, int targetIndex)
{
	return myInts[sourceIndex][targetIndex];
}

// a breadth first search
void Graph::BreadthFirstSearch(string startingVertex)
{
	cout << "\n starting BFS with vertex " << startingVertex << endl;
	string srce[MAX];
	int weight[MAX];
	int solidified[MAX];
	int next = 0;
	int smallest = 0;

	int change = 0;

	for (size_t i = 0; i < MAX; i++)
	{
		srce[i] = " ";
		weight[i] = INFINITE; // INFINITE means no path
		solidified[i] = 0; // 0 means not solidified, 1 means solidified
	}
	for (size_t i = 0; i < MAX; i++)
	{
		if (startingVertex == myChars.at(i))
		{
			// no source
			weight[i] = 0; // no weight, so set to zero
			next = i; // first item
			break;
		}
	}
	do
	{
		
		cout << "\t visited " << myChars[next] << endl;
		solidified[next] = 1;
		for (size_t j = 0; j < MAX; j++)
		{
			if (myInts[next][j] > -1 && (weight[next] + myInts[next][j]) < weight[j])
			{
				weight[j] = weight[next] + myInts[next][j];
				srce[j] = myChars[next];
			}
		}
		change = 0;
		smallest = INFINITE;
		
		for (size_t i = 0; i < MAX; i++)
		{
			if (solidified[i] == 0)
			{
				if (weight[i] < smallest)
				{
					next = i;
					smallest = weight[i];
					change = 1;
				}
			}
		}
		if (change == 0)
		{
			break;
		}
	} while (true);
}

// shortest path search
void Graph::DijkstraShortedPath(string startingVertex)
{
	cout << "\n shortest distance starting with " << startingVertex << endl;
	string srce[MAX];
	int weight[MAX];
	int solidified[MAX];
	int next = 0;
	int smallest = 0;

	int change = 0;
	string path;
	for (size_t i = 0; i < MAX; i++)
	{
		srce[i] = " ";
		weight[i] = INFINITE; // INFINITE means no path
		solidified[i] = 0; // 0 means not solidified, 1 means solidified
	}
	for (size_t i = 0; i < MAX; i++)
	{
		if (startingVertex == myChars.at(i))
		{
			// no source
			weight[i] = 0; // no weight, so set to zero
			next = i; // first item
			break;
		}
	}
	do
	{
		change = 0;
		solidified[next] = 1;
		for (size_t j = 0; j < MAX; j++)
		{
			if (myInts[next][j] > -1 && (weight[next] + myInts[next][j]) < weight[j])
			{
				weight[j] = weight[next] + myInts[next][j];
				srce[j] = myChars[next];
			}
		}
		
		smallest = INFINITE;

		for (size_t i = 0; i < MAX; i++)
		{
			if (solidified[i] == 0)
			{
				if (weight[i] < smallest)
				{
					next = i;
					smallest = weight[i];
					change = 1;
				}
			}
		}
		if (change == 0)
		{
			break;
		}
	} while (true);

	for (size_t i = 0; i < MAX; i++)
	{
		cout << "\t to: " << myChars[i] << "  ";
		if (weight[i] == INFINITE)
		{
			cout << "no path";
		}
		else {
			cout << weight[i] << "\tPath: " << myChars[i];
			path = srce[i];
			do
			{
				for (size_t j = 0; j < MAX; j++)
				{
					if (path == myChars.at(j))
					{
						cout << " " << path;
						path = srce[j];
						break;
					}
				}
				if (path == " ")
				{
					break;
				}
			} while (true);
		}
		cout << endl;
	}
}

// print the graph
void Graph::PrintGraph()
{
	cout << " ";
	for (size_t i = 0; i < myChars.size(); i++)
	{
		cout << "\t" << myChars[i];
	}
	cout << endl;
	for (size_t i = 0; i < myChars.size(); i++)
	{
		cout << myChars[i] << "\t";
		for (size_t j = 0; j < MAX; j++)
		{
			if (myInts[i][j] > -1)
			{
				cout << myInts[i][j] << "\t";
			}
			else
			{
				cout << " \t";
			}
		}
		cout << endl;
	}
}


