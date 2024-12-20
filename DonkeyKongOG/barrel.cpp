#include "barrel.h"
#include "mario.h"

char Barrel::findBarrelNextChar(char currChar, char charBelow)
{
	switch (charBelow)
	{
	case point::FLOOR:
		return barrel.getBoard()->getChar(barrel.getX() + barrel.getDiffX(), barrel.getY());
		break;
	case point::RFLOOR:
		return barrel.getBoard()->getChar(barrel.getX() + 1, barrel.getY());
		break;
	case point::LFLOOR:
		return barrel.getBoard()->getChar(barrel.getX() - 1, barrel.getY());
		break;
	case point::OPEN_SPACE:
		return barrel.getBoard()->getChar(barrel.getX(), barrel.getY() + 1);
		break;
	case mario::MARIO: 
		return mario::MARIO;
		break;
	}
}

point::States Barrel::findBarrelState(char currChar, char nextChar, char charBelow)
{
	
	if (barrel.isFalling(currChar))
	{
		return point::States::FALLING;
	}
	else
		return point::States::WALKING_OR_STAYING;
}


void Barrel::moveBarrel()
{
	barrel.draw(BARREL);
	Sleep(100);
	barrel.erase();

	point::States state;
	char currChar, nextChar, charBelow;

	currChar = barrel.getBoard()->getChar(barrel.getX(), barrel.getY());
	charBelow = barrel.getBoard()->getChar(barrel.getX(), barrel.getY() + 1);
	nextChar = findBarrelNextChar(currChar, charBelow);
	state = findBarrelState(currChar, nextChar, charBelow);

	switch (state)
	{
	case point::States::FALLING:
		barrel.move(0, 1);
		break;
	case point::States::WALKING_OR_STAYING:
		if (isExploding())
		{
			barrel.erase();
			//barrel.getBoard()->setChar(barrel.getX(), barrel.getY(), point::OPEN_SPACE);
		}
		else
		{
		   barrelWalking(charBelow);
		   barrel.setHightFalling(0);
		}
		break;

	}
}

void Barrel::barrelWalking(char charBelow)
{
	switch (charBelow)
	{
	case point::FLOOR:
		barrel.move(barrel.getDiffX(), 0);
		break;
	case point::RFLOOR:
		barrel.move(1, 0);
		break;
	case point::LFLOOR:
		barrel.move(-1, 0);
		break;
	default:
		break;
	}
}
