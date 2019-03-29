#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

#include "HashMap.h"

using namespace std;

void CleanString(string& line)
{
	// make string all lowercase
	transform(line.begin(), line.end(), line.begin(), tolower);

	// replace punctuation with white-space
	auto cursor = line.begin();
	while (cursor != line.end())
	{
		if (*cursor < 'a' || *cursor > 'z')
			*cursor = ' ';
		cursor++;
	}
}

void FindLargestWordCount(HashMap& hm, string &key, int& maxValue)
{
	auto start = hm.begin();
	auto end = hm.end();
	key = *start;
	hm.GetKeyValue(*start, maxValue);
	++start;

	while (start != end)
	{
		int value = 0;
		hm.GetKeyValue(*start, value);
		if (value > maxValue)
		{
			key = *start;
			maxValue = value;
		}
		++start;
	}
}

int main()
{
	// NOTE: no path information. 
	// Check your dev environment to see where the "default" location is and make sure the text file is there
	ifstream myFile("readThis.txt");
	if (myFile.is_open())
	{
		string line;
		stringstream ss;

		HashMap hm(500);

		while (getline(myFile, line))
		{
			// pull each individual word from the line
			CleanString(line);

			stringstream ss(line);
			string word;
			while (ss >> word)
			{
				if (word.length() > 1)
				{
					int currentCount = 0;
					hm.GetKeyValue(word, currentCount);		// get the current count for this word
					hm.SetKeyValue(word, currentCount + 1);	// inc the count for this word
				}
			}
		}
		string mostCommon;
		int value = -1;
		cout << "Most common words are:" << endl;
		for (size_t i = 0; i < 25; i++)
		{
			string mostCommon;
			int value = -1;

			FindLargestWordCount(hm, mostCommon, value);
			cout << mostCommon << "\t\t" << value << endl;

			hm.SetKeyValue(mostCommon, -1);	// set the count negative so it won't appear on the next iteration
		}
		myFile.close();
	}

	cout << endl << "press the [Enter] key to exit" << endl;
	getchar();
	return 0;
}