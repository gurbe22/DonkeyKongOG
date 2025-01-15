#ifndef POINT_H
#define POINT_H

#include "utils.h"
#include "board.h"  
#include <iostream>

// The 'point' class represents a point on a game board, including its position, movement, and interactions.
class point
{
    int x; // Current x-coordinate of the point
    int y; // Current y-coordinate of the point
    int diff_x; // Change in x-coordinate (velocity or direction)
    int diff_y; // Change in y-coordinate (velocity or direction)
    int heightFalling = 0; // Tracks the height the point has fallen
    Board* pBoard = nullptr; // Pointer to the associated game board

    // Checks if a position is outside the board limits
    bool isOutOfLimit(int newPos_x, int newPos_y);


public:
    // Enumeration representing the different states of the point's movement or action
    enum class States { FALLING, JUMPING, CLIMBING, WALKING_OR_STAYING, EXPLODING };

    

    // Constructor initializing the point's position and setting movement to zero
    point(const int xStart = 0, const int yStart = 0) : x(xStart), y(yStart) { diff_x = 0; diff_y = 0; }
   
    // Moves the point by updating its velocity in x and y directions
    void move(int newDiff_X, int newDiff_Y);

    // Draws the point at its current position using the given character
    void draw(char ch) const
    {
        gotoxy(x, y); // Moves the cursor to the specified position
        std::cout << ch;
    }

    // Erases the point from the board by restoring the original character
    void erase() const
    {
        char ch;
        ch = pBoard->getChar(x, y); // Retrieves the character at the point's position on the board
        draw(ch);
    }

    // Sets the associated game board
    void setBoard(Board& board) {
        pBoard = &board;
    }

    // Accessor methods to get and set the x-coordinate
    int getX() const { return x; }
    void setX(int newX) { x = newX; }

    // Accessor methods to get and set the y-coordinate
    int getY() const { return y; }
    void setY(int newY) { y = newY; }

    // Accessor methods to get and set the x-direction velocity
    int getDiffX() const { return diff_x; }
    void setDiffX(int newDiff_x) { diff_x = newDiff_x; }

    // Accessor methods to get and set the y-direction velocity
    int getDiffY() const { return diff_y; }
    void setDiffY(int newDiff_y) { diff_y = newDiff_y; }

    // Returns a pointer to the associated game board
    Board* getBoard() const { return pBoard; }

    // Checks if the given character represents a floor
    bool isFloor(char nextChar)
    {
        return nextChar == gameConfig::FLOOR || nextChar == gameConfig::LFLOOR || nextChar == gameConfig::RFLOOR;
    }

    // Accessor methods to get and set the height the point has fallen
    int getHeightFalling() const { return heightFalling; }
    void setHightFalling(int newHeightFalling) { heightFalling = newHeightFalling; }

    // Determines if the point is currently falling based on the given character
    bool isFalling(char currChar);

    // Checks if the point is currently on a floor
    bool isOnFloor();
};

#endif