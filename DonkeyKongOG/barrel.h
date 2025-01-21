#ifndef BARREL_H
#define BARREL_H

#include "point.h"
#include "gameConfig.h"
#include "Board.h"
#include "enemy.h"
using namespace std;

// The Barrel class represents barrels in the game, which move and interact with the game world.
class Barrel : public enemy
{
    static constexpr int HEIGHT_TO_EXPLODE = 8; // Height after which the barrel explodes
    bool explode = false; // Indicates whether the barrel has exploded

    // Determines the next character the barrel interacts with
    char findBarrelNextChar(char currChar, char charBelow);

    // Determines the current state of the barrel (e.g., falling or walking)
    point::States findBarrelState(char currChar);

    // Checks if the barrel is exploding
    bool isExploding() { 
        return (myEnemy.getHeightFalling() >= HEIGHT_TO_EXPLODE);
    }

    // Handles the barrel's walking logic based on the floor type
    void barrelWalking(char charBelow);

public:
    // Constructor to initialize the barrel with an optional delay
    Barrel(Board& board, int ghostStartingX, int ghostStartingY)
        : enemy(board, ghostStartingX, ghostStartingY) {}

    // Moves the barrel based on its state
    void moveBarrel();

    // Draws the barrel on the board
    void draw() const override
    {
        myEnemy.draw(gameConfig::BARREL);
    }

    // Sets whether the barrel is in an exploded state
    void setExplode(bool newExplode) { explode = newExplode; }

    // Gets whether the barrel is in an exploded state
    bool getIsExplode() const { return explode; }
};

#endif
