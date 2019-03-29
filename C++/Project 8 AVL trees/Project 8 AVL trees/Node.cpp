/*
I, Benjamin Jones, certify that I wrote all of the code presented here
on my own, with exception of the code given to us from the instructor
4/7/2018
*/

#include "stdafx.h"
#include "Node.h"


Node::Node()
{
	RightChild = nullptr;
	LeftChild = nullptr;
	depth = 0;
	range = 0;
}

Node::Node(int data)
{
	this->data = data;
	RightChild = nullptr;
	LeftChild = nullptr;
	depth = 0;
	range = 0;
}


Node::~Node()
{
}


