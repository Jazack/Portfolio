#pragma once
#include <string>

class Node
{
public:
	Node()
	{
		count = 0;
	}
	Node(std::string input)
	{
		word = input;
		count = 1;
		next = nullptr;
	}
	Node(std::string input, int count)
	{
		word = input;
		this->count = count;
		next = nullptr;
	}
	Node(std::string input, int count, Node *next)
	{
		word = input;
		this->count = count;
		this->next = next;
	}
	~Node() = default; // really nothing to destruct

	Node *next;
	std::string word;	// this is the "key"
	unsigned int count;	// this is the "value"
};

