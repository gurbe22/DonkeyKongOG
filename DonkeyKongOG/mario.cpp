#include "mario.h"


void mario::move(gameConfig::eKeys &key)
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
	
	case gameConfig::eKeys::DOWN_Y:
		myMario.setDiffY(1);
		break;
	
    }

	int x, y;
	x = myMario.getX();
	y = myMario.getY();
	nextChar = myMario.getBoard()->getChar(x + myMario.getDiffX(), y + myMario.getDiffY());
	currChar = myMario.getBoard()->getChar(x, y);


	switch (key)
	{
	case gameConfig::eKeys::UP:
		if (currChar == 'H')
		{
			if (nextChar == 'H')
			{
				myMario.setDiffX(0);
				myMario.setDiffY(-1);
			}
			else if (nextChar == '=' || nextChar == '<' || nextChar == '>')
			{
				myMario.setDiffX(0);
				myMario.setDiffY(-2);
				key = gameConfig::eKeys::STAY;
			}
		}
		else if (isOnFloor() || heightJumping == 1 || heightJumping == 2 )
		{
			myMario.setDiffY(-1);
			heightJumping++;
			
		}
		// else
		// {
		// 	myMario.setDiffX(0);
		// 	myMario.setDiffY(0);
		// }
		break;
	case gameConfig::eKeys::DOWN:
		if (currChar == 'H')
		{
			if (nextChar == 'H')
			{
				myMario.setDiffX(0);
				myMario.setDiffY(1);
			}
			else
			{
				myMario.setDiffX(0);
				myMario.setDiffY(0);
			}
		}
		else if(myMario.getBoard()->getChar(x, y + 2) == 'H')
		{
			myMario.setDiffX(0);
			myMario.setDiffY(2);
		}
		else
		{
			myMario.setDiffX(0);
			myMario.setDiffY(0);
		}
		break;
	}

	if ((nextChar == 'Q' || nextChar == '=' || nextChar == '<' || nextChar == '>') && currChar != 'H')
	{
		myMario.setDiffX(0);
		myMario.setDiffY(0);
	}

	char chBelow = myMario.getBoard()->getChar(x, y + 1);
	if (chBelow == ' ' && heightJumping != 1 && heightJumping != 2)
	{
		//myMario.setDiffX(0);
		myMario.setDiffY(1);
		if (heightJumping == 3)
		{
			heightJumping = 0;
			//myMario.setDiffY(1);
			key = gameConfig::eKeys::DOWN_Y;
		}
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
