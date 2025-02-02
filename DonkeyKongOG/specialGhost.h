#ifndef SPECIAL_GHOST_H
#define SPECIAL_GHOST_H

#include "point.h"
#include "GameConfig.h"
#include "board.h"
#include <cstdlib> // For rand()
#include "ghost.h"
#include "enemy.h"

class SpecialGhost : public Ghost
{
    // Change the direction along the X-axis
    void changeDirectionX() override
    {
        direction = (direction == GameConfig::directions::RIGHT)
            ? GameConfig::directions::LEFT
            : GameConfig::directions::RIGHT;
    }

    // Change the direction along the Y-axis
    void changeDirectionY() override
    {
        direction = (direction == GameConfig::directions::DOWN)
            ? GameConfig::directions::UP
            : GameConfig::directions::DOWN;
    }

    // Prevent collision with other enemies
    void preventCollision(std::vector<Enemy*>& enemies) override;

public:
    // Constructor: Initializes the SpecialGhost with starting coordinates
    SpecialGhost(Board& board, int specialGhostStartingX, int specialGhostStartingY)
        : Ghost(board, specialGhostStartingX, specialGhostStartingY) {}

    // Destructor: Default implementation from the Ghost class
    ~SpecialGhost() override = default;

    // Move the special ghost while considering possible collisions with enemies
    void move(std::vector<Enemy*>& enemies) override;

    // Draw the SpecialGhost using the predefined symbol from the GameConfig
    void draw() const override { myEnemy.draw(GameConfig::SPECIAL_GHOST); }

    // Return false since SpecialGhost cannot explode
    bool getIsExplode() const override { return false; };
};

#endif
