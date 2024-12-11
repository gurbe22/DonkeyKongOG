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

	if (nextChar == 'Q' || nextChar == '=' || nextChar == '<' || nextChar == '>') 
	{
		    myMario.setDiffX(0); 
		    myMario.setDiffY(0); 
	}

	if (currChar == 'H')
	{
		if (nextChar == 'H' && key == gameConfig::eKeys::UP)
		{
			myMario.setDiffX(0);
			myMario.setDiffY(-1);
		}
		else if (nextChar == 'Q' || nextChar == '=' || nextChar == '<' || nextChar == '>')
		{
			if (key == gameConfig::eKeys::UP)
			{
				myMario.setDiffX(0);
				myMario.setDiffY(-1);
			}
			else if(key == gameConfig::eKeys::DOWN)
			{
				myMario.setDiffX(0);
				myMario.setDiffY(1);
			}
		}
	}

	if (currChar == ' ' && key == gameConfig::eKeys::UP && myMario.getBoard()->getChar(x, y + 1) == 'H')
	{
		myMario.setDiffX(0);
		myMario.setDiffY(0);
	}
	
	myMario.setX(x + myMario.getDiffX()); 
	myMario.setY(y + myMario.getDiffY()); 
}

void mario::draw(char c)
{
	myMario.draw(c);
}

void mario::erase()
{
	char c;
	int x, y;
	Board* b;

	b = myMario.getBoard();

	x = myMario.getX();
	y = myMario.getY();
	c = b->getChar(x,y);
	myMario.draw(c);
}
