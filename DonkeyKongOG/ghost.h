#ifndef GHOST_H
#define GHOST_H

#include "point.h"
#include "GameConfig.h"
#include "board.h"
#include <cstdlib> // For rand()
#include "enemy.h"

class SpecialGhost; // Forward declaration for potential interactions

// The 'Ghost' class represents a basic enemy that moves left and right.
class Ghost : public Enemy
{
protected:
    GameConfig::directions direction = GameConfig::directions::RIGHT; // Initial movement direction

    // Function to change direction (only LEFT or RIGHT)
    virtual void changeDirectionX() override
    {
        direction = (direction == GameConfig::directions::RIGHT)
            ? GameConfig::directions::LEFT
            : GameConfig::directions::RIGHT;
    }

    // Ghost does not move vertically, so this function is empty
    virtual void changeDirectionY() override {}

    // Prevent collisions between ghosts (to be implemented in move logic)
    virtual void preventCollision(std::vector<Enemy*>& enemies);

public:
    // Constructor initializes the ghost at a given position
    Ghost(Board& board, int ghostStartingX, int ghostStartingY)
        : Enemy(board, ghostStartingX, ghostStartingY) {}

    ~Ghost() override = default; // Virtual destructor for proper cleanup

    // Moves the ghost based on its direction and checks for collisions
    void move(std::vector<Enemy*>& enemies) override;

    // Draws the ghost on the board
    void draw() const override { myEnemy.draw(GameConfig::GHOST); }

    // Ghosts do not explode, so this always returns false
    bool getIsExplode() const override { return false; }

    // Returns the ghost's current movement direction
    GameConfig::directions getDirection() const { return direction; }
};

#endif
