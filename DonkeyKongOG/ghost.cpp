#include "ghost.h"
using namespace std;

void Ghost::move(vector<Enemy*>& enemies) {
	// Check if the ghost is in the air
	int currentX = myEnemy.getX();
	int currentY = myEnemy.getY();
	int belowY = currentY + 1;

	// Keep moving the ghost down while there is no floor beneath it and it's within bounds
	if (isWithinBounds(currentX, belowY) &&
		!GameConfig::isFloor(myEnemy.getBoard()->getChar(currentX, belowY))) {
		myEnemy.move(0, 1); // Move the ghost one step down
		return;
	}

	// If the ghost is on the ground, proceed with normal movement
	// 5% chance to randomly change direction
	if (rand() % 100 < 5) {
		changeDirection();
	}

	int maxAttempts = 2; // Maximum attempts to move in a direction
	while (maxAttempts > 0) {
		// Check for collisions with other ghosts
		preventCollision(enemies);
		int nextX = myEnemy.getX() + static_cast<int>(direction);
		int nextY = myEnemy.getY();
		int belowNextX = nextX;
		int belowNextY = nextY + 1;



		// If movement is not valid, change direction and retry
		if (!isWithinBounds(nextX, nextY) ||
			!GameConfig::isFloor(myEnemy.getBoard()->getChar(belowNextX, belowNextY))||
			GameConfig::isFloor(myEnemy.getBoard()->getChar(nextX, nextY)))
		{
			changeDirection();
			maxAttempts--;
			continue;
		}

		// If movement is valid, perform the move and exit the function
		myEnemy.move(static_cast<int>(direction), 0);
		return;
	}

	// If all attempts fail, the ghost stays in place
	return;
}


void Ghost::preventCollision(vector<Enemy*>& enemies) {
	for (auto& otherGhost : enemies) {
		Ghost* pb = dynamic_cast<Ghost*>(otherGhost);
		if (otherGhost == this || !pb) continue; // Skip self-comparison

		int nextX = myEnemy.getX() + static_cast<int>(direction);
		int nextY = myEnemy.getY();
		int otherX = otherGhost->getX();
		int otherY = otherGhost->getY();

		// Check if ghosts would collide
		if (nextX == otherX && nextY == otherY) {
			// Ghosts are moving towards each other, change direction
			changeDirection();
			otherGhost->changeDirection();
			return; // Exit after handling the collision prevention
		}
	}
}
