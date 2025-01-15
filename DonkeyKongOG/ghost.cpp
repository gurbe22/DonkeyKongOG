#include "ghost.h"

void ghost::moveGhost() {
    // 5% סיכוי לשינוי כיוון אקראי
    if (rand() % 100 < 5) {
        changeDirection();
    }

    int maxAttempts = 2; // ניסיונות מקסימליים
    while (maxAttempts > 0) {
        int nextX = myGhost.getX() + static_cast<int>(direction);
        int nextY = myGhost.getY();
        int belowNextX = nextX;
        int belowNextY = nextY + 1;
        /*
        if (myGhost.getBoard() == nullptr) {
            std::cerr << "Error: Board is not assigned to the ghost!" << std::endl;
            return; // לא ניתן להמשיך ללא לוח
        }
        
        char belowTile = myGhost.getBoard()->getChar(belowNextX, belowNextY);
        if (belowTile == '\0') {
            std::cerr << "Warning: Tile at (" << belowNextX << ", " << belowNextY << ") is empty (\\0)." << std::endl;
        }
        */
        // אם לא ניתן לנוע, שנה כיוון ונסה שוב
        if (!isWithinBounds(nextX, nextY) ||
            !isMovableTile(myGhost.getBoard()->getChar(belowNextX, belowNextY))) {
            changeDirection();
            maxAttempts--;
            continue;
        }

        // אם ניתן לנוע, בצע תנועה וסיים את הפונקציה
        myGhost.move(static_cast<int>(direction), 0);
        return;
    }

    // אם נגמרו הניסיונות, הרוח נשארת במקום
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
