#include "point.h"
#include "board.h" 


bool point::isOutOfLimit(int newPos_x, int newPos_y)  
{
	return (newPos_x >= gameConfig::GAME_WIDTH - 1 ||
		newPos_y >= gameConfig::GAME_HEIGHT - 1 ||
		newPos_x <= 0 ||
		newPos_y <= 0);
}



void point::move(int newDiff_X, int newDiff_Y) 
{
	int newPos_x = x + newDiff_X;
	int newPos_y = y + newDiff_Y;
	char nextChar = pBoard->getChar(newPos_x, newPos_y); 

	if (isOutOfLimit(newPos_x, newPos_y) || isFloor(nextChar))
	{
		newDiff_X = 0;
		newDiff_Y = 0;
	}

	diff_x = newDiff_X;
	diff_y = newDiff_Y;

	x += diff_x;
	y += diff_y;
}