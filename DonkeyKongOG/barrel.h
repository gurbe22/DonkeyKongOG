#ifndef BARREL_H
#define BARREL_H

#include "point.h"
#include "GameConfig.h"
#include "board.h"
#include "enemy.h"

// The Barrel class represents barrels in the game, which move and interact with the game world.
class Barrel : public Enemy
{
    static constexpr int HEIGHT_TO_EXPLODE = 8; // Height threshold for explosion
    bool explode = false; // Tracks explosion state

    // Determines if the barrel is falling or walking
    Point::States findBarrelState(char currChar) const;

    // Checks if the barrel should explode based on falling height
    bool isExploding() const {
        return (myEnemy.getHeightFalling() >= HEIGHT_TO_EXPLODE);
    }

    // Handles the barrel's movement logic when walking on different surfaces
    void barrelWalking(char charBelow);

    // Sets explosion state
    void setExplode(bool newExplode) { explode = newExplode; }

public:
    // Constructor to initialize the barrel with a starting position
    Barrel(Board& board, int ghostStartingX, int ghostStartingY)
        : Enemy(board, ghostStartingX, ghostStartingY) {}

    ~Barrel() override = default;

    // Moves the barrel based on its current state
    void move(std::vector<Enemy*>& enemies) override;

    // Draws the barrel using its designated character
    void draw() const override
    {
        myEnemy.draw(GameConfig::BARREL);
    }

    // Returns whether the barrel has exploded
    bool getIsExplode() const override { return explode; }

    // Placeholder functions for changing direction (not implemented)
    void changeDirectionX() {}
    void changeDirectionY() {}
};

#endif
