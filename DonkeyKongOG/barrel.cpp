#include "barrel.h"
using namespace std;

// Determines the next character the barrel interacts with
char Barrel::findBarrelNextChar(char currChar, char charBelow) const
{
	switch (charBelow)
	{
	case GameConfig::FLOOR:
	case GameConfig::LIMIT:
		return myEnemy.getBoard()->getChar(myEnemy.getX() + myEnemy.getDiffX(), myEnemy.getY());

	case GameConfig::RFLOOR:
		return myEnemy.getBoard()->getChar(myEnemy.getX() + 1, myEnemy.getY());

	case GameConfig::LFLOOR:
		return myEnemy.getBoard()->getChar(myEnemy.getX() - 1, myEnemy.getY());

	case GameConfig::OPEN_SPACE:
		return myEnemy.getBoard()->getChar(myEnemy.getX(), myEnemy.getY() + 1);

	case GameConfig::MARIO:
		return GameConfig::MARIO;
	default:
		return charBelow;

	}
}

// Determines the current state of the barrel (e.g., falling or walking)
Point::States Barrel::findBarrelState(char currChar) const
{
	return myEnemy.isFalling(currChar) ? Point::States::FALLING : Point::States::WALKING_OR_STAYING;
}

// Moves the barrel based on its state
void Barrel::move()
{
	char currChar = myEnemy.getBoard()->getChar(myEnemy.getX(), myEnemy.getY());
	char charBelow = myEnemy.getBoard()->getChar(myEnemy.getX(), myEnemy.getY() + 1);
	char nextChar = findBarrelNextChar(currChar, charBelow);
	Point::States state = findBarrelState(currChar);

	switch (state)
	{
	case Point::States::FALLING:
		// Move the barrel downward if it is falling
		myEnemy.move(0, 1);
		break;
	case Point::States::WALKING_OR_STAYING:
		if (isExploding())
		{
			// Handle explosion logic if the barrel is exploding
			myEnemy.erase();
			setExplode(true);
		}
		else
		{
			// Handle barrel walking logic
			barrelWalking(charBelow);
			myEnemy.setHeightFalling(0);
		}
		break;
	default:
		// take no action
		break;
	}
}

// Handles the barrel's walking logic based on the floor type
void Barrel::barrelWalking(char charBelow)
{
	int diffX = getDiffX();
	switch (charBelow)
	{
	case GameConfig::FLOOR:
	case GameConfig::LIMIT:
		// Move the barrel in its current horizontal direction
		if (diffX == 0)
		{
			myEnemy.erase();
			setExplode(true);
		}
		else
		{
			myEnemy.move(diffX, 0);
		}
		break;
	case GameConfig::RFLOOR:
		// Move the barrel to the right
		myEnemy.move(1, 0);
		break;
	case GameConfig::LFLOOR:
		// Move the barrel to the left
		myEnemy.move(-1, 0);
		break;
	default:
		// Do nothing if the floor type is not recognized
		break;
	}
	if (myEnemy.isOutOfLimit(getX(), getY() + 1))
	{
		myEnemy.erase();
		setExplode(true); // Out of bounds
	}
}