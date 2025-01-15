#include "ghost.h"

void ghost::moveGhost(vector<ghost>& ghosts) {
    // Check if the ghost is in the air
    int currentX = myGhost.getX();
    int currentY = myGhost.getY();
    int belowY = currentY + 1;

    // Keep moving the ghost down while there is no floor beneath it and it's within bounds
    if (isWithinBounds(currentX, belowY) &&
        !isMovableTile(myGhost.getBoard()->getChar(currentX, belowY))) {
        myGhost.move(0, 1); // Move the ghost one step down
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
        preventCollision(ghosts);
        int nextX = myGhost.getX() + static_cast<int>(direction);
        int nextY = myGhost.getY();
        int belowNextX = nextX;
        int belowNextY = nextY + 1;

        

        // If movement is not valid, change direction and retry
        if (!isWithinBounds(nextX, nextY) ||
            !isMovableTile(myGhost.getBoard()->getChar(belowNextX, belowNextY))) {
            changeDirection();
            maxAttempts--;
            continue;
        }

        // If movement is valid, perform the move and exit the function
        myGhost.move(static_cast<int>(direction), 0);
        return;
    }

    // If all attempts fail, the ghost stays in place
    return;
}


bool ghost::isWithinBounds(int x, int y) const {
    return x >= 0 && x < gameConfig::GAME_WIDTH && y >= 0 && y < gameConfig::GAME_HEIGHT;
}

bool ghost::isMovableTile(char tile) const {
    // רצפה או משטח חוקי לתנועה
    return tile == gameConfig::FLOOR ||
        tile == gameConfig::LFLOOR ||
        tile == gameConfig::RFLOOR;
}

void ghost::preventCollision(vector<ghost>& ghosts) {
    for (auto& otherGhost : ghosts) {
        if (&otherGhost == this) continue; // Skip self-comparison

        // Check if the ghosts are moving towards each other
        int nextX = myGhost.getX() + static_cast<int>(direction);
        int nextY = myGhost.getY();
        int otherX = otherGhost.myGhost.getX();
        int otherY = otherGhost.myGhost.getY();

        if (nextX == otherX && nextY == otherY) {
            // Ghosts are moving towards each other, change direction
            changeDirection();
            otherGhost.changeDirection();
            return; // Exit after handling the collision prevention
        }
    }
}
