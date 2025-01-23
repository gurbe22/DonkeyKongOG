#ifndef POINT_H
#define POINT_H

#include "utils.h"
#include "board.h"  
#include <iostream>

// The 'point' class represents a point on a game board, including its position, movement, and interactions.
class Point
{
    int x = 0;                       // Current x-coordinate of the point
    int y = 0;                       // Current y-coordinate of the point
    int diff_x = 0;                  // Change in x-coordinate (velocity or direction)
    int diff_y = 0;                  // Change in y-coordinate (velocity or direction)
    int heightFalling = 0;           // Tracks the height the point has fallen
    Board* pBoard = nullptr;         // Pointer to the associated game board

    // Checks if a position is outside the board limits
    bool isOutOfLimit(int newPos_x, int newPos_y) const;

public:
    // Enumeration representing the different states of the point's movement or action
    enum class States { FALLING, JUMPING, CLIMBING, WALKING_OR_STAYING, EXPLODING};

    // Constructor initializing the point's position and setting movement to zero
    explicit Point(const int xStart = 0, const int yStart = 0) : x(xStart), y(yStart) {}
   
    // Moves the point by updating its velocity in x and y directions
    void move(int newDiff_X, int newDiff_Y);

    // Draws the point at its current position using the given character
    inline void draw(char ch) const
    {
        gotoxy(x, y); // Moves the cursor to the specified position
        std::cout << ch;
    }

    // Erases the point from the board by restoring the original character
    inline void erase() const
    {
        draw(pBoard->getChar(x, y));
    }
    inline void eraseCompletely () const
    {
        draw(GameConfig::OPEN_SPACE); 
    }

    // Sets the associated game board
    inline void setBoard(Board& board) 
    {
        pBoard = &board;
    }

    // Accessor methods for x-coordinate
    inline int getX() const { return x; }
    inline void setX(int newX) { x = newX; }

    // Accessor methods for y-coordinate
    inline int getY() const { return y; }
    inline void setY(int newY) { y = newY; }

    // Accessor methods for x-direction velocity
    inline int getDiffX() const { return diff_x; }
    inline void setDiffX(int newDiff_x) { diff_x = newDiff_x; }

    // Accessor methods for y-direction velocity
    inline int getDiffY() const { return diff_y; }
    inline void setDiffY(int newDiff_y) { diff_y = newDiff_y; }

    // Returns a pointer to the associated game board
    inline Board* getBoard() const { return pBoard; }

    // Accessor methods for heightFalling
    inline int getHeightFalling() const { return heightFalling; }
    inline void setHeightFalling(int newHeightFalling) { heightFalling = newHeightFalling; }

    // Determines if the point is currently falling based on the given character
    bool isFalling(char currChar) const;

    // Checks if the point is currently on a floor
    bool isOnFloor() const;
};

#endif