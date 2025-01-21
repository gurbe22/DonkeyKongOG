#include "enemy.h"

bool enemy::isWithinBounds(int x, int y) const
{
	return x >= 0 && x < gameConfig::GAME_WIDTH && y >= 0 && y < gameConfig::GAME_HEIGHT;
}
