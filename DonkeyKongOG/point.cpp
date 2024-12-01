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
	char nextChar, currChar;
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

	nextChar = pBoard->getChar(x + diff_x, y + diff_y);
	currChar = pBoard->getChar(x, y);
	
	if (nextChar == 'Q' || nextChar == '=' || nextChar == '<' || nextChar == '>') {
		diff_x = 0;
		diff_y = 0;
	}

	/*if (nextChar == ' ' && key == gameConfig::eKeys::UP)
	{
		diff_x = 0; 
		diff_y = 0;
	}*/

	if (currChar == 'H')
	{
		if (nextChar == 'H' && key == gameConfig::eKeys::UP)
		{
			diff_x = 0;
			diff_y = -1;
		}
		else if (nextChar == 'H' && key == gameConfig::eKeys::DOWN)
		{
			diff_x = 0;
			diff_y = 1;
		}
		/*else if (currChar == ' ' && key == gameConfig::eKeys::UP && pBoard->getChar(x, y + 1) == 'H')
		{
			diff_x = 0;
			diff_y = 0;
		}*/
	}

	if (currChar == ' ' && key == gameConfig::eKeys::UP && pBoard->getChar(x, y + 1) == 'H')
	{
		diff_x = 0;
		diff_y = 0;
	}

	x += diff_x;
	y += diff_y;
}
