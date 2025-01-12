#include "ghost.h"

void ghost::moveGhost()
{

	int randNum = rand() % 100;
	if (randNum < 5)
	{	{
		// Change direction randomly
		changeDirection();
	}
	char nextChar = myGhost.getBoard()->getChar(myGhost.getX() + (int)direction, myGhost.getY());
	char belowNextChar;
	if (isOutOfLimits())
	{
		changeDirection();
		//moveGhost();
	}
		// Move the ghost in the specified direction
		switch (belowNextChar)
		{
		case gameConfig::FLOOR:
		case gameConfig::LFLOOR:
		case gameConfig::RFLOOR:

			break;
		
		default:
			changeDirection();
			break;
		}
	}
	myGhost.move((int)direction, 0);

	
}
