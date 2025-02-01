#ifndef GHOST_H
#define GHOST_H

#include "point.h"
#include "GameConfig.h"
#include "board.h"
#include <cstdlib> // For rand()
#include "enemy.h"

class SpecialGhost;
class Ghost : public Enemy
{
protected:
    GameConfig::directions direction = GameConfig::directions::RIGHT;

    // Function to change direction (only LEFT or RIGHT)
    virtual void changeDirectionX() override
    {
        direction = (direction == GameConfig::directions::RIGHT)
            ? GameConfig::directions::LEFT
            : GameConfig::directions::RIGHT;
    }

	virtual void changeDirectionY() override {}


    // Prevent collisions between ghosts (to be implemented)
    virtual void preventCollision(std::vector<Enemy*>& enemies);

public:
    Ghost(Board& board, int ghostStartingX, int ghostStartingY)
        : Enemy(board, ghostStartingX, ghostStartingY) {}

    ~Ghost() override = default;

    void move(std::vector<Enemy*>& enemies) override;
   /* void move() override {};*/

    void draw() const override { myEnemy.draw(GameConfig::GHOST); }

    bool getIsExplode() const override { return false; };

	GameConfig::directions getDirection() const { return direction; }
};

#endif
