#include "point.h"

// Checks if the new position is outside the boundaries of the game board
bool Point::isOutOfLimit(int newPos_x, int newPos_y) const
{
	const bool outRight = (newPos_x >= GameConfig::GAME_WIDTH);
	const bool outBottom = (newPos_y >= GameConfig::GAME_HEIGHT);
	const bool outLeft = (newPos_x < 0);
	const bool outTop = (newPos_y <= 0);

	return outRight || outBottom || outLeft || outTop;
}

// Moves the point by updating its position and checking for limits or collisions
void Point::move(int newDiff_X, int newDiff_Y)
{
	// Calculate the new potential position
	int newPos_x = x + newDiff_X;
	int newPos_y = y + newDiff_Y;
	char nextChar = pBoard->getChar(newPos_x, newPos_y);

	// Check if the new position is out of limits or hits a floor
	if (isOutOfLimit(newPos_x, newPos_y) || GameConfig::isFloor(nextChar))
	{
		newDiff_X = 0; // Stop horizontal movement
		newDiff_Y = 0; // Stop vertical movement
	}

	// Update velocity
	diff_x = newDiff_X;
	diff_y = newDiff_Y;

	// Update falling height if moving downward
	heightFalling = (diff_y == 1) ? heightFalling + 1 : 0;

	// Updating the new position of the point
	x += diff_x;
	y += diff_y;
}

// Checks if the point is currently falling based on the character below it
bool Point::isFalling(char currChar) const
{
	if (isOutOfLimit(x, y + 1))
		return false; // Out of bounds

	if (currChar == GameConfig::LADDER)
		return false; // Hammer is not falling

	if (isOnFloor())
		return false; // On the floor

	return true; // Point is falling
}

// Determines if the point is standing on a floor
bool Point::isOnFloor() const
{
	char charBelow = pBoard->getChar(x, y + 1);
	return GameConfig::isFloor(charBelow) || y == GameConfig::GAME_HEIGHT - 1;
}
