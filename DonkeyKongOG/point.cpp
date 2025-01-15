#include "point.h"

// Checks if the new position is outside the boundaries of the game board
bool point::isOutOfLimit(int newPos_x, int newPos_y)
{
    return (newPos_x >= gameConfig::GAME_WIDTH - 1 || // Right boundary
        newPos_y >= gameConfig::GAME_HEIGHT ||   // Bottom boundary
        newPos_x <= 0 ||                        // Left boundary
        newPos_y <= 0);                         // Top boundary
}

// Moves the point by updating its position and checking for limits or collisions
void point::move(int newDiff_X, int newDiff_Y)
{
    // Calculate the new potential position
    int newPos_x = x + newDiff_X;
    int newPos_y = y + newDiff_Y;
    char nextChar = pBoard->getChar(newPos_x, newPos_y);

    // Check if the new position is out of limits or hits a floor
    if (isOutOfLimit(newPos_x, newPos_y) || isFloor(nextChar))
    {
        newDiff_X = 0; // Stop horizontal movement
        newDiff_Y = 0; // Stop vertical movement
    }

    // Update velocity
    diff_x = newDiff_X;
    diff_y = newDiff_Y;

    // If moving downwards, increase the falling height counter
    if (diff_y == 1)
    {
        heightFalling++;
    }
    else
    {
        heightFalling = 0; // Reset falling height if not falling
    }

    // Updating the new position of the point
    x += diff_x;
    y += diff_y;
}

// Checks if the point is currently falling based on the character below it
bool point::isFalling(char currChar)
{
    // If the current character represents open space
    if (currChar == gameConfig::OPEN_SPACE)
    {
        // Check if the point is not standing on a floor
        if (isOnFloor() == false)
        {
            return true; // The point is falling
        }
    }
    return false; // The point is not falling
}

// Determines if the point is standing on a floor
bool point::isOnFloor()
{
    // Get the character directly below the point
    char ch1Below = pBoard->getChar(x, y + 1);

    // Check if the character below represents any type of floor
    return (ch1Below == gameConfig::FLOOR ||
        ch1Below == gameConfig::LFLOOR ||
        ch1Below == gameConfig::RFLOOR);
}
