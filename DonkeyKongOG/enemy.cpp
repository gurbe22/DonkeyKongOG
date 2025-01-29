#include "enemy.h"
using namespace std;

bool Enemy::isWithinBounds(int x, int y) const
{
	return x >= 0 && x < GameConfig::GAME_WIDTH && y >= 0 && y < GameConfig::GAME_HEIGHT;
}
