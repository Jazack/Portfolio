/*
This class is a library to simplify changing the color of the background and the text
*/
#pragma once
#include <iostream>
#include <Windows.h>

using namespace std;

class ConsoleControls
{
private:
	const int BLACK = 0;
	const int DARKBLUE = 1; // DANIEL
	const int DARKCYAN = 2;
	const int DARKRED = 3; // DEATH
	const int DARKMAGENTA = 4;// alice
	const int DARKYELLOW = 5; // DYING FROM ALISTAIR
	const int DARKGRAY = 6; 
	const int GRAY = 7; // EFFECTS
	const int BLUE = 8; // BARIMUS
	const int GREEN = 9; // INVENTORY
	const int CYAN = 10; // DONOVO
	const int RED = 11; // PAIN (FIGHTS)
	const int MAGENTA = 12; // store
	const int YELLOW = 13; // ALISTAIR
	const int WHITE = 14; // THE PLAYER
	const int DARKGREEN = 15; // MONSTERS

	const string BACKGROUND = "BACKGROUND";
	const string FOREGROUND = "FOREGROUND";

public:
	ConsoleControls();
	ConsoleControls(string place, int color);
	void SetBackground(int color);
	void setForeground(int color);
	~ConsoleControls();
};

