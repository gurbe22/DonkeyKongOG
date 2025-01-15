#include "ghost.h"

void ghost::moveGhost() {
    // 5% ����� ������ ����� �����
    if (rand() % 100 < 5) {
        changeDirection();
    }

    int maxAttempts = 2; // �������� ���������
    while (maxAttempts > 0) {
        int nextX = myGhost.getX() + static_cast<int>(direction);
        int nextY = myGhost.getY();
        int belowNextX = nextX;
        int belowNextY = nextY + 1;
        /*
        if (myGhost.getBoard() == nullptr) {
            std::cerr << "Error: Board is not assigned to the ghost!" << std::endl;
            return; // �� ���� ������ ��� ���
        }
        
        char belowTile = myGhost.getBoard()->getChar(belowNextX, belowNextY);
        if (belowTile == '\0') {
            std::cerr << "Warning: Tile at (" << belowNextX << ", " << belowNextY << ") is empty (\\0)." << std::endl;
        }
        */
        // �� �� ���� ����, ��� ����� ���� ���
        if (!isWithinBounds(nextX, nextY) ||
            !isMovableTile(myGhost.getBoard()->getChar(belowNextX, belowNextY))) {
            changeDirection();
            maxAttempts--;
            continue;
        }

        // �� ���� ����, ��� ����� ����� �� ��������
        myGhost.move(static_cast<int>(direction), 0);
        return;
    }

    // �� ����� ���������, ���� ����� �����
    return;
}


bool ghost::isWithinBounds(int x, int y) const {
    return x >= 0 && x < gameConfig::GAME_WIDTH && y >= 0 && y < gameConfig::GAME_HEIGHT;
}

bool ghost::isMovableTile(char tile) const {
    // ���� �� ���� ���� ������
    return tile == gameConfig::FLOOR ||
        tile == gameConfig::LFLOOR ||
        tile == gameConfig::RFLOOR;
}
