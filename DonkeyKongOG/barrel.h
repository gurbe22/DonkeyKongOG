#ifndef BARREL_H
#define BARREL_H

#include "point.h"
#include "gameConfig.h"
#include "Board.h"
using namespace std;

// The Barrel class represents barrels in the game, which move and interact with the game world.
class Barrel
{
    point barrel; // Represents the barrel's position and state
    static constexpr int HEIGHT_TO_EXPLODE = 8; // Height after which the barrel explodes

    //int startDelay; // Delay before the barrel starts moving
    //int currentFrame; // Tracks the current frame of the barrel's movement
    bool explode = false; // Indicates whether the barrel has exploded

    // Determines the next character the barrel interacts with
    char findBarrelNextChar(char currChar, char charBelow);

    // Determines the current state of the barrel (e.g., falling or walking)
    point::States findBarrelState(char currChar, char nextChar, char charBelow);

    // Checks if the barrel is exploding
    bool isExploding() { 
        return (barrel.getHeightFalling() >= HEIGHT_TO_EXPLODE);
    }

    // Handles the barrel's walking logic based on the floor type
    void barrelWalking(char charBelow);

public:
	Barrel(); // Default constructor

    // Constructor to initialize the barrel with an optional delay
    Barrel( int barrelStartingX, int barrelStartingY, Board& board)
        : barrel(barrelStartingX, barrelStartingY)
        {
            this->setBoard(board);
        }

    // Moves the barrel based on its state
    void moveBarrel();

    // Sets the board the barrel interacts with
    void setBoard(Board& board)
    {
        barrel.setBoard(board);
    }

    // Gets the board the barrel interacts with
    Board* getBoard() const
    {
        return barrel.getBoard();
    }

    // Gets the X-coordinate of the barrel
    int getX() const
    {
        return barrel.getX();
    }

    // Gets the Y-coordinate of the barrel
    int getY() const
    {
        return barrel.getY();
    }

    // Draws the barrel on the board
    void drawBarrel() const
    {
        barrel.draw(gameConfig::BARREL);
    }

    // Erases the barrel from the board
    void eraseBarrel() const
    {
        barrel.erase();
    }

    // Sets whether the barrel is in an exploded state
    void setExplode(bool newExplode) { explode = newExplode; }

    // Gets whether the barrel is in an exploded state
    bool getIsExplode() const { return explode; }

	int getDiffX() const { return barrel.getDiffX(); }
	int getDiffY() const { return barrel.getDiffY(); }
};

#endif
