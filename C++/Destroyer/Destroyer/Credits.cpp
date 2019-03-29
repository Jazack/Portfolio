#include "Credits.h"
#pragma once
#include "Opening.h"
#include <string>
#include <iostream>
#include<cstdlib>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <amp_graphics.h>

using namespace std;

Credits::Credits()
{
	
	system("CLS");
	cout << "GAME DESIGN: Benjamin Jones\n\nGAME STORY: Benjamin Jones\n\nPROGRAMMER: Benjamin Jones\n\nSPECIAL THANKS TO MICROSOFT FOR PERMITTING STUDENTS TO HAVE VISUAL STUDIOS\n\n";
	system("PAUSE");
}


Credits::~Credits()
{
}
