#include "barrel.h"


Barrel::Barrel() {};

// Determines the next character the barrel interacts with
char Barrel::findBarrelNextChar(char currChar, char charBelow)
{
	switch (charBelow)
	{
	case gameConfig::FLOOR:
		// Get the character in the direction of barrel movement on the '=' floor
		return barrel.getBoard()->getChar(barrel.getX() + barrel.getDiffX(), barrel.getY());
	case gameConfig::RFLOOR:
		// Get the character to the right of the barrel on a '>' floor
		return barrel.getBoard()->getChar(barrel.getX() + 1, barrel.getY());
	case gameConfig::LFLOOR:
		// Get the character to the left of the barrel on a '<' floor
		return barrel.getBoard()->getChar(barrel.getX() - 1, barrel.getY());
	case gameConfig::OPEN_SPACE:
		// Get the character directly below the barrel in open space
		return barrel.getBoard()->getChar(barrel.getX(), barrel.getY() + 1);
	case gameConfig::MARIO:
		// Return Mario's character if the barrel interacts with Mario
		return gameConfig::MARIO;
	}
}

// Determines the current state of the barrel (e.g., falling or walking)
point::States Barrel::findBarrelState(char currChar, char nextChar, char charBelow)
{
	if (barrel.isFalling(currChar))
	{
		// If the barrel is falling
		return point::States::FALLING;
	}
	else
	{
		// If the barrel is not falling, it is walking or staying
		return point::States::WALKING_OR_STAYING;
	}
}

// Moves the barrel based on its state
void Barrel::moveBarrel()
{
	// Variables for barrel state and surroundings
	point::States state;
	char currChar, nextChar, charBelow;

	// Get the characters at and around the barrel's position
	currChar = barrel.getBoard()->getChar(barrel.getX(), barrel.getY());
	charBelow = barrel.getBoard()->getChar(barrel.getX(), barrel.getY() + 1);
	nextChar = findBarrelNextChar(currChar, charBelow);
	state = findBarrelState(currChar, nextChar, charBelow);

	switch (state)
	{
	case point::States::FALLING:
		// Move the barrel downward if it is falling
		barrel.move(0, 1);
		break;
	case point::States::WALKING_OR_STAYING:
		if (isExploding())
		{
			// Handle explosion logic if the barrel is exploding
			barrel.erase();
			setExplode(true);
		}
		else
		{
			// Handle barrel walking logic
			barrelWalking(charBelow);
			barrel.setHightFalling(0);
		}
		break;
	}
}

// Handles the barrel's walking logic based on the floor type
void Barrel::barrelWalking(char charBelow)
{
	int diffX = barrel.getDiffX();
	switch (charBelow)
	{
	case gameConfig::FLOOR:
		// Move the barrel in its current horizontal direction
		if (diffX == 0)
		{
			setExplode(true);
		}
		else
		{
			barrel.move(diffX, 0);
		}
		break;
	case gameConfig::RFLOOR:
		// Move the barrel to the right
		barrel.move(1, 0);
		break;
	case gameConfig::LFLOOR:
		// Move the barrel to the left
		barrel.move(-1, 0);
		break;
	default:
		// Do nothing if the floor type is not recognized
		break;
	}
}