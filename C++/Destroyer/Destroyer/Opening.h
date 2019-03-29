#pragma once
#include <string>
#include <iostream>

using namespace std;

class Opening
{
private:
	const string CREDITS = "C";
	const string START = "S";
	const string END = "E";
	const string LOAD = "L";
	string choice = "ZERO";


public:
	Opening();
	int Display();
	string getChoice();
	int SwitchLocations();
	int UserChoice();
	~Opening();
};

