#include "ConsoleControls.h"



ConsoleControls::ConsoleControls()
{
}



#pragma region Paramateered initializer
ConsoleControls::ConsoleControls(string place, int colors)
{
	if (place == BACKGROUND)
		SetBackground(colors);
	else
		setForeground(colors);
}

#pragma endregion
// MAKE THE BLACK BACKGROUND WORK
#pragma region Set Back Ground
void ConsoleControls::SetBackground(int color)
{

#pragma region Color control Starter

	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// MAKES IT YELLOW

#pragma endregion
#pragma region CONSTANTS
	const int BLACK = 0;
	const int DARKBLUE = 1;
	const int DARKCYAN = 2;
	const int DARKRED = 3;
	const int DARKMAGENTA = 4;
	const int DARKYELLOW = 5;
	const int DARKGRAY = 6;
	const int GRAY = 7;
	const int BLUE = 8;
	const int GREEN = 9;
	const int CYAN = 10;
	const int RED = 11;
	const int MAGENTA = 12;
	const int YELLOW = 13;
	const int WHITE = 14;
	const int DARKGREEN = 15;
#pragma endregion

	switch (color)
	{
	case BLACK:
		SetConsoleTextAttribute(hconsole, COLOR_BACKGROUND);
		break;
	case DARKBLUE:
		SetConsoleTextAttribute(hconsole, BACKGROUND_BLUE);
		break;
	case DARKGREEN:
		SetConsoleTextAttribute(hconsole, BACKGROUND_GREEN);
		break;
	case DARKCYAN:
		SetConsoleTextAttribute(hconsole, BACKGROUND_GREEN | BACKGROUND_BLUE);
		break;
	case DARKRED:
		SetConsoleTextAttribute(hconsole, BACKGROUND_RED);
		break;
	case DARKMAGENTA:
		SetConsoleTextAttribute(hconsole, BACKGROUND_RED | BACKGROUND_BLUE);
		break;
	case DARKYELLOW:
		SetConsoleTextAttribute(hconsole, BACKGROUND_RED | BACKGROUND_GREEN);
		break;
	case DARKGRAY:
		SetConsoleTextAttribute(hconsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		break;
	case GRAY:
		SetConsoleTextAttribute(hconsole, BACKGROUND_INTENSITY);
		break;
	case BLUE:
		SetConsoleTextAttribute(hconsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE);
		break;
	case GREEN:
		SetConsoleTextAttribute(hconsole, BACKGROUND_INTENSITY | BACKGROUND_GREEN);
		break;
	case CYAN:
		SetConsoleTextAttribute(hconsole, BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE);
		break;
	case RED:
		SetConsoleTextAttribute(hconsole, BACKGROUND_INTENSITY | BACKGROUND_RED);
		break;
	case MAGENTA:
		SetConsoleTextAttribute(hconsole, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE);
		break;
	case YELLOW:
		SetConsoleTextAttribute(hconsole, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN);
		break;
	case WHITE:
		SetConsoleTextAttribute(hconsole, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		break;
	default:
		break;
	}
}
#pragma endregion

#pragma region ForeGround / text

void ConsoleControls::setForeground(int color)
{

#pragma region Color control Starter

	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// MAKES IT YELLOW

#pragma endregion
#pragma region CONSTANTS
	const int BLACK = 0;
	const int DARKBLUE = 1;
	const int DARKCYAN = 2;
	const int DARKRED = 3;
	const int DARKMAGENTA = 4;
	const int DARKYELLOW = 5;
	const int DARKGRAY = 6;
	const int GRAY = 7;
	const int BLUE = 8;
	const int GREEN = 9;
	const int CYAN = 10;
	const int RED = 11;
	const int MAGENTA = 12;
	const int YELLOW = 13;
	const int WHITE = 14;
	const int DARKGREEN = 15;
#pragma endregion

	switch (color)
	{
	case BLACK:
		SetConsoleTextAttribute(hconsole, 0);
		break;
	case DARKBLUE:
		SetConsoleTextAttribute(hconsole, FOREGROUND_BLUE);
		break;
	case DARKGREEN:
		SetConsoleTextAttribute(hconsole, FOREGROUND_GREEN);
		break;
	case DARKCYAN:
		SetConsoleTextAttribute(hconsole, FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case DARKRED:
		SetConsoleTextAttribute(hconsole, FOREGROUND_RED);
		break;
	case DARKMAGENTA:
		SetConsoleTextAttribute(hconsole, FOREGROUND_RED | FOREGROUND_BLUE);
		break;
	case DARKYELLOW:
		SetConsoleTextAttribute(hconsole, FOREGROUND_RED | FOREGROUND_GREEN);
		break;
	case DARKGRAY:
		SetConsoleTextAttribute(hconsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case GRAY:
		SetConsoleTextAttribute(hconsole, FOREGROUND_INTENSITY);
		break;
	case BLUE:
		SetConsoleTextAttribute(hconsole, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
		break;
	case GREEN:
		SetConsoleTextAttribute(hconsole, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		break;
	case CYAN:
		SetConsoleTextAttribute(hconsole, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case RED:
		SetConsoleTextAttribute(hconsole, FOREGROUND_INTENSITY | FOREGROUND_RED);
		break;
	case MAGENTA:
		SetConsoleTextAttribute(hconsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
		break;
	case YELLOW:
		SetConsoleTextAttribute(hconsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		break;
	case WHITE:
		SetConsoleTextAttribute(hconsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	default:
		break;
	}

}

#pragma endregion
ConsoleControls::~ConsoleControls()
{
}
