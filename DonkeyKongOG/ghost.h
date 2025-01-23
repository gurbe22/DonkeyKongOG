#ifndef GHOST_H
#define GHOST_H

#include "point.h"
#include "GameConfig.h"
#include "board.h"
#include <cstdlib> // For rand()
#include "enemy.h"


class Ghost : public Enemy
{
	GameConfig::directions direction = GameConfig::directions::RIGHT;
	
	// Function to change the direction of the ghost
	void changeDirection()
	{
		direction == GameConfig::directions::RIGHT ? direction = GameConfig::directions::LEFT : direction = GameConfig::directions::RIGHT;
	}

	// Function to prevent collisions between ghosts
	void preventCollision(std::vector<Ghost>& ghosts);

public:
	
	Ghost( Board &board,int ghostStartingX, int ghostStartingY)
		: Enemy(board, ghostStartingX, ghostStartingY ){}

	void moveGhost (std::vector<Ghost>& ghosts);
	
	void draw() const override { myEnemy.draw(GameConfig::GHOST); }
	
	int getDirectionX() const { return static_cast<int>(direction);}
	int getDirectionY() const { return 0; }
};

#endif