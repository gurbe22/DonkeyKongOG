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

     void changeDirectionX() override
     {
      direction = (direction == GameConfig::directions::RIGHT)
              ? GameConfig::directions::LEFT
              : GameConfig::directions::RIGHT;
     }
    
     void changeDirectionY() override
     {
      direction = (direction == GameConfig::directions::DOWN)
    	  ? GameConfig::directions::UP
    	  : GameConfig::directions::DOWN;
     }

    void preventCollision(std::vector<Enemy*>& enemies) override;
    
public:

    SpecialGhost(Board& board, int specialGhostStartingX, int specialGhostStartingY)
        :  Ghost(board, specialGhostStartingX, specialGhostStartingY){}

    ~SpecialGhost() override = default;

    void move(std::vector<Enemy*>& enemies) override;
    void move() override {};

    void draw() const override { myEnemy.draw(GameConfig::SPECIAL_GHOST); }

    bool getIsExplode() const override { return false; };

};

#endif