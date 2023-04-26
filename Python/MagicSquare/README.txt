Python Magic Square
Created by Benjamin Jones

This program generates a magic square
Magic squares are filled with numbers such that the following conditions are met:
	1) each opposite coordinates equal to the same value
	2) all columns and rows equate to the same value
	3) no digit is repeated
This program generates small magic squares. It can easily handle squares smaller than 9x9,
at 9x9 through 13x13 it has a harder time generating it, but can usually handle situations
where it is given a starting value double the recommended value
above 15x15 it rarely works, even with larger starting values.
This is because there is a timeout feature that will often limit the attempts allowed of larger squares to one iteration,
which iterations become quite long.

The program will first ask for the size of the magic square, which allows for any odd, positive, value.
Afterwards, it will ask for the starting value, which must be equal to or larger than the magic square size squared, divided by two, and then adding one.
Or, one more than half the total available spaces on the grid.

The numbers selected will be from 1 to one less than double the starting value.

The output of the magic square will be set so that it is divided into columns and rows, such as this 13x13:
289, 062, 361, 397, 203, 249, 326, 296, 492, 111, 104, 128, 232, 
353, 021, 369, 024, 050, 494, 196, 309, 375, 239, 416, 109, 295, 
334, 248, 307, 439, 242, 016, 140, 206, 002, 495, 433, 112, 276, 
099, 054, 371, 308, 004, 305, 421, 418, 447, 136, 135, 133, 419, 
456, 151, 400, 057, 355, 473, 344, 146, 148, 218, 074, 321, 107, 
047, 457, 059, 263, 477, 182, 160, 460, 029, 110, 485, 138, 383, 
384, 198, 030, 071, 412, 366, 250, 134, 088, 429, 470, 302, 116, 
117, 362, 015, 390, 471, 040, 340, 318, 023, 237, 441, 043, 453, 
393, 179, 426, 282, 352, 354, 156, 027, 145, 443, 100, 349, 044, 
081, 367, 365, 364, 053, 082, 079, 195, 496, 192, 129, 446, 401, 
224, 388, 067, 005, 498, 294, 360, 484, 258, 061, 193, 252, 166, 
205, 391, 084, 261, 125, 191, 304, 006, 450, 476, 131, 479, 147, 
268, 372, 396, 389, 008, 204, 174, 251, 297, 103, 139, 438, 211,

In the previous output, it will be noted that the starting value was 250, found at the center of the array. The values in the other squares will all range between 1 and 499.
