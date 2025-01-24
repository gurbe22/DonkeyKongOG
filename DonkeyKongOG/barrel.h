#ifndef BARREL_H
#define BARREL_H

#include "point.h"
#include "GameConfig.h"
#include "board.h"
#include "enemy.h"


// The Barrel class represents barrels in the game, which move and interact with the game world.
class Barrel : public Enemy
{
    static constexpr int HEIGHT_TO_EXPLODE = 8; // Height after which the barrel explodes
    bool explode = false; // Indicates whether the barrel has exploded

    // Determines the next character the barrel interacts with
    char findBarrelNextChar(char currChar, char charBelow) const;

    // Determines the current state of the barrel (e.g., falling or walking)
    Point::States findBarrelState(char currChar) const;

    // Checks if the barrel is exploding
    bool isExploding() const { 
        return (myEnemy.getHeightFalling() >= HEIGHT_TO_EXPLODE);
    }

    // Handles the barrel's walking logic based on the floor type
    void barrelWalking(char charBelow);

	// Sets whether the barrel is in an exploded state
	void setExplode(bool newExplode) { explode = newExplode; }

public:
    // Constructor to initialize the barrel with an optional delay
    Barrel(Board& board, int ghostStartingX, int ghostStartingY)
        : Enemy(board, ghostStartingX, ghostStartingY) {}

    ~Barrel() override = default;

    // Moves the barrel based on its state
    void move() override;

    void move(std::vector<Enemy*>& enemies) override {};

    // Draws the barrel on the board
    void draw() const override
    {
        myEnemy.draw(GameConfig::BARREL);
    }

    // Gets whether the barrel is in an exploded state
    bool getIsExplode() const override { return explode; }

    void changeDirection() override {};

};

#endif
