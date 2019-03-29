/*I Benjamin Jones have not used any code other than my own(or that in the textbook)
for this project.I also have not used any function or data - structure from the Standard - Template Library.
I understand that any violation of this disclaimer will result in a 0 for the project.*/
#include "stdafx.h"
#include "HashMap.h"

HashMap::HashMap(int size)
{
	hashArray = new Node*[size];
	for (int i = 0; i < size; i++)
	{
		hashArray[i] = nullptr;
	}
	sizeOfArray = size;
	totalElements = 0;
}

HashMap::~HashMap()
{
	for (int i = 0; i < sizeOfArray; i++)
	{
		Node *tempNode = hashArray[i];
		int j = 0;
		do
		{
			if (tempNode == nullptr)
			{
				j--;
				break;
			}
			tempNode = tempNode->next;
			j++;
		} while (true);

		for (j = j; j > 0; j--)
		{
			tempNode = hashArray[i];
			for (int i = 0; i < j; i++)
			{
				tempNode = tempNode->next;
			}
			delete tempNode;
		}
	}
}

bool HashMap::IsKeyPresent(string const & key) const
{
	int theSize = 0;
	bool trueFalse = false;
	theSize = GenerateHash(key);
	if (hashArray[theSize % sizeOfArray] != nullptr)
	{
		Node *thisNode = hashArray[theSize % sizeOfArray];
		do
		{
			if (thisNode->word == key)
			{
				trueFalse = true;
				break;
			}
			if (thisNode->next == nullptr)
			{
				break;
			}
			thisNode = thisNode->next;
		} while (true);
	}

	return trueFalse;
}

void HashMap::SetKeyValue(string const & key, int value)
{
	int theSize = 0;
	theSize = GenerateHash(key);

	if (hashArray[theSize % sizeOfArray] != nullptr)
	{
		Node *thisNode = hashArray[theSize % sizeOfArray];
		do
		{
			if (thisNode->word == key)
			{
				thisNode->count = value;
				break;
			}
			if (thisNode->next == nullptr)
			{
				thisNode->next = new Node(key, value);
				totalElements++;
				break;
			}
			thisNode = thisNode->next;
		} while (true);
	}
	else
	{
		hashArray[theSize % sizeOfArray] = new Node(key, value);
		totalElements++;
	}
}

bool HashMap::GetKeyValue(string const & key, int & value)
{
	int theSize = 0;
	bool trueFalse = false;
	theSize = GenerateHash(key);

	if (hashArray[theSize % sizeOfArray] != nullptr)
	{
		Node *thisNode = hashArray[theSize % sizeOfArray];
		do
		{
			if (thisNode->word == key)
			{
				value = thisNode->count;
				trueFalse = true;
				break;
			}
			if (thisNode->next == nullptr)
			{
				// state that there are currently zero of the item
				value = 0;
				break;
			}
			thisNode = thisNode->next;
		} while (true);
	}

	return trueFalse;
}

Iterator HashMap::begin()
{
	int non_null = 0;
	do {
		if (hashArray[non_null] == nullptr)
		{
			non_null++;
		}
		else
		{
			break;
		}
	} while (true);
	return Iterator(non_null, hashArray, sizeOfArray);
}

Iterator HashMap::end()
{
	Iterator tempIterator = Iterator(sizeOfArray - 1, hashArray, sizeOfArray);
	// go to the end of the Iterator
	do
	{
		if (tempIterator.is_item())
		{
			++tempIterator;
		}
		else
		{
			break;
		}
	} while (true);
	return tempIterator;
}

int HashMap::GenerateHash(string key) const
{
	int theSize = 0;
	char temp;
	for (size_t i = 0; i < key.size(); i++)
	{
		temp = key[i];
		theSize += static_cast<int>(temp);
	}
	return theSize;
}
