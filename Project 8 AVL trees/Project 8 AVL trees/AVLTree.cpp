/*
I, Benjamin Jones, certify that I wrote all of the code presented here
on my own, with exception of the code given to us from the instructor, which is
"Project 8 AVL trees.cpp
4/7/2018
*/

#include "stdafx.h"
#include "AVLTree.h"


AVLTree::AVLTree()
{
	head = nullptr;
}


AVLTree::~AVLTree()
{
}

void AVLTree::Insert(int store)
{
	if (head == nullptr)
	{
		head = new Node(store);
	}
	else
	{
		InsertHelper(store, head);
	}
	//for the head
	int range = balanceStart(head);
	RotateDeterminer(head);
}

void AVLTree::PreOrderTraversal()
{

	PreOrderHelper(head);
	cout << endl;
}

void AVLTree::Print()
{
	printHelper(head, 0);
}

int AVLTree::InsertHelper(int store, Node * myNode)
{
	int depth = 0;
	if (store <= myNode->data)
	{
		if (myNode->RightChild == nullptr)
		{
			myNode->RightChild = new Node(store);
		}
		else
		{
			depth = InsertHelper(store, myNode->RightChild);
		}
		
	}
	else
	{
		if (myNode->LeftChild == nullptr)
		{
			myNode->LeftChild = new Node(store);
		}
		else
		{
			depth = InsertHelper(store, myNode->LeftChild);
		}
	}
	
	int range = balanceStart(myNode);
	RotateDeterminer(myNode);

	return depth++;
}

int AVLTree::PreOrderHelper(Node * myNode)
{
	int depth = 0;
	cout << myNode->data << " ";
	if (myNode->RightChild != nullptr || myNode->LeftChild != nullptr)
	{

	if (myNode->RightChild != nullptr)
	{
		depth = PreOrderHelper(myNode->RightChild);
	}
	if (myNode->LeftChild != nullptr)
	{
		depth = PreOrderHelper(myNode->LeftChild);
	}
	
	depth++;
	}
	myNode->depth = depth;
	return depth;
}

void AVLTree::RightRotate(Node * top, Node * Node1)
{
	Node *tmp = new Node(top->data);

	tmp->LeftChild = top->LeftChild;
	tmp->RightChild = Node1->LeftChild;
	top->LeftChild = tmp;
	top->data = Node1->data;
	top->RightChild = Node1->RightChild;
	delete Node1;
}

void AVLTree::LeftRotate(Node * top, Node * Node1)
{
	Node *tmp = new Node(top->data);
	tmp->RightChild = top->RightChild;
	tmp->LeftChild = Node1->RightChild;
	top->RightChild = tmp;
	top->data = Node1->data;
	top->LeftChild = Node1->LeftChild;
	delete Node1;
}

int AVLTree::balanceFactor(Node * Node1)
{
	int left = 0;
	int right = 0;

		if (Node1->LeftChild != nullptr)
		{
			left = balanceFactor(Node1->LeftChild);
			left++;
		}
		if (Node1->RightChild != nullptr)
		{
			right = balanceFactor(Node1->RightChild);
			right++;
		}
	
	if (right > left)
	{
		return right;
	}
	return left;
}

int AVLTree::balanceStart(Node * Node1)
{
	int left = 0;
	int right = 0;
	if (Node1->LeftChild != nullptr)
	{
		left = balanceFactor(Node1->LeftChild);
		left++;
	}
	if (Node1->RightChild != nullptr)
	{
		right = balanceFactor(Node1->RightChild);
		right++;
	}
	Node1->range = left - right;
	
	return (left - right);
}

void AVLTree::RotateDeterminer(Node * Node1)
{
	if (Node1 != nullptr)
	{
		if (Node1->range == -TWO && Node1->RightChild->range == 1)
		{
			LeftRotate(Node1->RightChild, Node1->RightChild->LeftChild);
			RightRotate(Node1, Node1->RightChild);
		}
		else if (Node1->range == -TWO && Node1->RightChild->range == -1)
		{
			RightRotate(Node1, Node1->RightChild);
		}
		else if (Node1->range == TWO && Node1->LeftChild->range == -1)
		{
			RightRotate(Node1->LeftChild, Node1->LeftChild->RightChild);
			LeftRotate(Node1, Node1->LeftChild);
		}
		else if (Node1->range == TWO && Node1->LeftChild->range == 1)
		{
			LeftRotate(Node1, Node1->LeftChild);
		}
	}
}

void AVLTree::printHelper(Node * Node1, int height)
{
	for (size_t i = 0; i < height; i++)
	{
		cout << "   ";
	}
	cout << Node1->data << " (" << Node1->depth << ")";
	if (Node1->depth == 0)
	{
		cout << " [LEAF]\n";
	}
	else
	{
		cout << endl;
	}
	if (Node1->depth != 0)
	{

		if (Node1->RightChild != nullptr)
		{
			printHelper(Node1->RightChild, height + 1);
		}
		else
		{
			for (size_t i = 0; i < height + 1; i++)
			{
				cout << "   ";
			}
			cout << "[EMPTY]\n";
		}
		if (Node1->LeftChild != nullptr)
		{
			printHelper(Node1->LeftChild, height + 1);
		}
		else
		{
			for (size_t i = 0; i < height + 1; i++)
			{
				cout << "   ";
			}
			cout << "[EMPTY]\n";
		}
	}
}




