/*
I, Benjamin Jones, certify that I wrote all of the code presented here
on my own, with exception of the code given to us from the instructor
4/7/2018
*/

#pragma once
#include "Node.h"
#include <iostream>
using namespace std;

class AVLTree
{
public:
	AVLTree();
	~AVLTree();
	void Insert(int store);
	void PreOrderTraversal();
	void Print();
	/*
	Constructor
		• Destructor
		• Insert
		• Print(indented print function like the one we did in class, but with each node’s height)
		• PreOrderTraversal
		*/
private:
	Node *head;
	
	int InsertHelper(int store, Node *myNode);
	int PreOrderHelper(Node *myNode);
	void RightRotate(Node * top, Node * Node1);
	void LeftRotate(Node *top, Node *Node1);
	int balanceFactor(Node *Node1);
	int balanceStart(Node *Node1);

	void RotateDeterminer(Node *Node1);

	void printHelper(Node *Node1, int height);

	const int TWO = 2;

	
};

