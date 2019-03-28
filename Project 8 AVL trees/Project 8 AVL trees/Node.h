/*
I, Benjamin Jones, certify that I wrote all of the code presented here
on my own, with exception of the code given to us from the instructor
4/7/2018
*/

#pragma once
class Node
{
public:
	Node();
	Node(int data);
	~Node();
	Node *RightChild;
	Node *LeftChild;

	int data;
	int depth;
	int range;
};

