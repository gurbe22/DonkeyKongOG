#include "point.h"
/*
void point::keyPressed(char key) {
	for (size_t i = 0; i < numKeys; i++) {
		if (std::tolower(key) == keys[i]) {
			dir = directions[i];
			return;
		}
	}
}
*/
void point::move(gameConfig::eKeys key)
{
	char ch;
	switch (key)
	{
	case gameConfig::eKeys::LEFT:
		diff_x = -1;
		diff_y = 0;
		break;
	case gameConfig::eKeys::RIGHT:
		diff_x = 1;
		diff_y = 0;
		break;
	case gameConfig::eKeys::UP:
		diff_x = 0;
		diff_y = -1;
		break;
	case gameConfig::eKeys::DOWN:
		diff_x = 0;
		diff_y = 1;
		break;
	case gameConfig::eKeys::STAY: 
		diff_x = 0;
		diff_y = 0;
		break;
    }

	ch = pBoard->getChar(x + diff_x, y + diff_y);
	
	if (ch == 'Q' || ch == '=' || ch == '<' || ch == '>') {
		diff_x = 0;
		diff_y = 0;
	}

	x += diff_x;

	

	// if (x > gameConfig::GAME_WIDTH - 1)
	// 	x = gameConfig::GAME_WIDTH - 1;
	// else if (x == 1)
	// 	x = 1;

	y += diff_y;
	// if (y > gameConfig::GAME_HEIGHT - 1)
	// 	y = gameConfig::GAME_HEIGHT - 1;
	// else if (y == 1)
	// 	y = 1;

	
}
