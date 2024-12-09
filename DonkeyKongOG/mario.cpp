#include "mario.h"

void mario::move(gameConfig::eKeys key)
{
	char nextChar, currChar;
	switch (key)
	{
	case gameConfig::eKeys::LEFT:
		myMario.setDiffX(- 1);  
		myMario.setDiffY(0);  
		break;
	case gameConfig::eKeys::RIGHT:
		myMario.setDiffX(1);
		myMario.setDiffY(0); 
		break;
	case gameConfig::eKeys::UP:
		myMario.setDiffX(0);
		myMario.setDiffY(-1);
		break;
	case gameConfig::eKeys::DOWN:
		myMario.setDiffX(0); 
		myMario.setDiffY(1);
		break;
	case gameConfig::eKeys::STAY:
		myMario.setDiffX(0);
		myMario.setDiffY(0);
		break;
	}

	int x, y;
	x = myMario.getX();
	y = myMario.getY();
	nextChar = myMario.getBoard()->getChar(x + myMario.getDiffX(), y + myMario.getDiffY());  
	currChar = myMario.getBoard()->getChar(x, y);  

	if (nextChar == 'Q' || nextChar == '=' || nextChar == '<' || nextChar == '>') {
		myMario.setDiffX(0); 
		myMario.setDiffY(0); 
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
			myMario.setDiffX(0);
			myMario.setDiffY(-1);
		}
		else if (nextChar == 'H' && key == gameConfig::eKeys::DOWN)
		{
			myMario.setDiffX(0);
			myMario.setDiffY(1);
		}
		/*else if (currChar == ' ' && key == gameConfig::eKeys::UP && pBoard->getChar(x, y + 1) == 'H')
		{
			diff_x = 0;
			diff_y = 0;
		}*/
	}

	if (currChar == ' ' && key == gameConfig::eKeys::UP && myMario.getBoard()->getChar(x, y + 1) == 'H')
	{
		myMario.setDiffX(0);
		myMario.setDiffY(0);
	}

	//x += diff_x;
	//y += diff_y;
	
	myMario.setX(x + myMario.getDiffX()); 
	myMario.setY(y + myMario.getDiffY()); 
}
