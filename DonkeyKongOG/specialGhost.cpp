#include "specialGhost.h"

using namespace std;

void SpecialGhost::move(vector<Enemy*>& enemies) {
	// Check if the ghost is in the air
	int currentX = myEnemy.getX();
	int currentY = myEnemy.getY();
	Board* board = myEnemy.getBoard();

	char currentChar = board->getChar(currentX, currentY);
	char belowChar = board->getChar(currentX, currentY + 1);
	char aboveChar = board->getChar(currentX, currentY - 1);
	char below2Char = board->getChar(currentX, currentY + 2);


	// Keep moving the ghost down while there is no floor beneath it and it's within bounds
	if (isWithinBounds(currentX, currentY + 1) &&
		!GameConfig::isFloor(board->getChar(currentX, currentY + 1))
		&& currentChar != GameConfig::LADDER) {
		myEnemy.move(0, 1); // Move the ghost one step down
		return;
	}
	//
	// If the ghost is on the ground, proceed with normal movement
	// 5% chance to randomly change direction
	if (direction != GameConfig::directions::DOWN && direction != GameConfig::directions::UP) 
	{
		if(rand() % 100 < 5)
			changeDirectionX();
	}

	if (currentChar == GameConfig::LADDER) {
		if (direction == GameConfig::directions::UP && aboveChar == GameConfig::LADDER) {
			myEnemy.move(0, -1);
			return;
		}
		if (direction == GameConfig::directions::UP && GameConfig::isFloor(aboveChar))
		{
			myEnemy.move(0, -2);
			return;
		}
		if (direction == GameConfig::directions::DOWN && belowChar == GameConfig::LADDER) {
			myEnemy.move(0, 1);
			return;
		}
	}

	if (below2Char == GameConfig::LADDER && myEnemy.isOnFloor()) {
		if (rand() % 2 == 0) {
			direction = GameConfig::directions::DOWN;
			myEnemy.move(0, 2);
			return;
		}
	}

	if (currentChar == GameConfig::LADDER && myEnemy.isOnFloor()) {
		if (rand() % 2 == 0) {
			direction = GameConfig::directions::UP;
			myEnemy.move(0, -1);
			return;
		}
	}


	int maxAttempts = 4; // Maximum attempts to move in a direction
	while (maxAttempts > 0) {
		// Check for collisions with other ghosts
		preventCollision(enemies);

		auto pos = GameConfig::directionPairs.at(direction);
		int nextX = myEnemy.getX() + pos.first;
		int nextY = myEnemy.getY() + pos.second;
		int belowNextX = nextX;
		int belowNextY = nextY + 1;
		

		// If movement is not valid, change direction and retry
		if (!isWithinBounds(nextX, nextY) ||
			!GameConfig::isFloor(board->getChar(belowNextX, belowNextY))||
			GameConfig::isFloor(board->getChar(nextX, nextY)))
		{
			changeDirectionX();
			maxAttempts--;
			continue;
		}

		
		// If movement is valid, perform the move and exit the function
		myEnemy.move(pos.first, pos.second);
		return;
	}
	// If all attempts fail, the ghost stays in place
	return;
}

void SpecialGhost::preventCollision(vector<Enemy*>& enemies) {
	for (auto& otherGhost : enemies) {
		Ghost* pb = dynamic_cast<Ghost*>(otherGhost);
		if (otherGhost == this || !pb ) continue; // Skip self-comparison

		const auto pos = GameConfig::directionPairs.at(direction);
		int nextX = myEnemy.getX() + pos.first;
		int nextY = myEnemy.getY() + pos.second;
		int otherX = otherGhost->getX();
		int otherY = otherGhost->getY();

		//GameConfig::directions otherDirection = pb ? pb->getDirection() : pbS->getDirection();
		GameConfig::directions otherDirection = pb->getDirection();
		const auto otherPos = GameConfig::directionPairs.at(otherDirection);
		int otherNextX = otherX + otherPos.first;
		int otherNextY = otherY + otherPos.second;


		// Check if ghosts would collide
		if (nextX == otherX && nextY == otherY) {
			if ((direction == GameConfig::directions::UP || direction == GameConfig::directions::DOWN) &&
			(otherDirection == GameConfig::directions::UP || otherDirection == GameConfig::directions::DOWN))
			{
				changeDirectionY();
				otherGhost->changeDirectionY();
			}
			else if ((direction == GameConfig::directions::UP || direction == GameConfig::directions::DOWN))
			{
				changeDirectionY();
			}
			else
			{
				changeDirectionX();
				otherGhost->changeDirectionX();
			}
			return; // Exit after handling the collision prevention
		}
	}
}