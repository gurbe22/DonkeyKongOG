#include "barrel.h"

char Barrel::findBarrelNextChar(char currChar, char charBelow)
{
	switch (charBelow)
	{
	case point::FLOOR:
		// Get the character in the direction of barrel movement on the '=' floor
		return barrel.getBoard()->getChar(barrel.getX() + barrel.getDiffX(), barrel.getY());
	case point::RFLOOR:
		// Get the character to the right of the barrel on a '>' floor
		return barrel.getBoard()->getChar(barrel.getX() + 1, barrel.getY());
	case point::LFLOOR:
		// Get the character to the left of the barrel on a '<' floor
		return barrel.getBoard()->getChar(barrel.getX() - 1, barrel.getY());
	case point::OPEN_SPACE:
		// Get the character directly below the barrel in open space
		return barrel.getBoard()->getChar(barrel.getX(), barrel.getY() + 1);
	case gameConfig::MARIO:
		// Return Mario's character if the barrel interacts with Mario
		return gameConfig::MARIO;
	}
}

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

void Barrel::moveBarrel()
{
	// Skip movement if the current frame is before the barrel's start delay
	if (currentFrame < startDelay) {
		currentFrame++;
		return;
	}

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

void Barrel::barrelWalking(char charBelow)
{
	switch (charBelow)
	{
	case point::FLOOR:
		// Move the barrel in its current horizontal direction
		barrel.move(barrel.getDiffX(), 0);
		break;
	case point::RFLOOR:
		// Move the barrel to the right
		barrel.move(1, 0);
		break;
	case point::LFLOOR:
		// Move the barrel to the left
		barrel.move(-1, 0);
		break;
	default:
		// Do nothing if the floor type is not recognized
		break;
	}
}
