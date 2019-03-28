/*I Benjamin Jones have not used any code other than my own(or that in the textbook)
for this project.I also have not used any function or data - structure from the Standard - Template Library.
I understand that any violation of this disclaimer will result in a 0 for the project.*/
#include "stdafx.h"
#include "HashMap.h"

Iterator::Iterator(int index, Node ** hashArray, int sizeOfArray)
{
	this->index = index;
	this->hashArray = hashArray;
	this->sizeOfArray = sizeOfArray;
	current = hashArray[index];
}

Iterator::Iterator()
{
}

string Iterator::operator*()
{
	return current->word;
}

void Iterator::operator++()
{
	if (is_item())
	{
		if (current == nullptr || current->next == nullptr)
		{
			current = hashArray[index];
			index++;
			// make sure that where it is going actually has something to point to
			do
			{
				if (current == nullptr)
				{
					current = hashArray[index];
					index++;
				}
				else
				{
					break;
				}
			} while (true);
		}
		else
		{
			current = current->next;
		}
	}
}

bool Iterator::operator!=(Iterator & other)
{
	if (current->next != other.current->next)
	{
		return true;
	}
	return false;
}

bool Iterator::is_item()
{
	if (index < sizeOfArray)
	{
		return true;
	}
	return false;
}

