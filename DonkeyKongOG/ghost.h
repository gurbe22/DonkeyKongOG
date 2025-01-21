#pragma once
#include "point.h"
#include "gameConfig.h"
#include "Board.h"
#include <cstdlib> // For rand()
#include "enemy.h"
using namespace std;

class ghost : public enemy
{
	enum class directions {
		LEFT = -1,   // Move left
		RIGHT = 1,  // Move right
	};
	//point myGhost;

	directions direction = directions::RIGHT;
	

	// Function to change the direction of the ghost
	void changeDirection()
	{
		direction == directions::RIGHT ? direction = directions::LEFT : direction = directions::RIGHT;
	}

	// Function to check if a tile is movable
	bool isMovableTile(char tile) const;

	// Function to prevent collisions between ghosts
	void preventCollision(vector<ghost>& ghosts);

public:
	
	ghost( Board &board,int ghostStartingX, int ghostStartingY)
		: enemy(board, ghostStartingX, ghostStartingY ){}

	void moveGhost (vector<ghost>& ghosts);
	
	void draw() const override
	{
		myEnemy.draw(gameConfig::GHOST);
	}
	

	int getDirectionX()
	{
		return static_cast<int>(direction);
	}
	int getDirectionY()
	{
		return 0;
	}
};

