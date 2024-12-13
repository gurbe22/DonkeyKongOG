#include "mario.h"

void mario::moveMario(gameConfig::eKeys& key)
{
	myMario.draw('@');
	Sleep(100);
	myMario.erase();
	point::States state; 
	char currChar, nextChar;
	currChar = myMario.getBoard()->getChar(myMario.getX(), myMario.getY());
	nextChar = findNextChar(currChar, key);
	state = findState(currChar, nextChar, key);

	switch (state)
	{
	case point::States::FALLING:
		myMario.move(0, 1);
		break;
	case point::States::JUMPING:
		jump(key, nextChar);
		break;
	case point::States::CLIMBING:
		climbing(nextChar, key);
		break;
	case point::States::WALKING_OR_STAYING:
		WalkingOrStaying(key);
		break;
	}
}

bool mario::isClimbing(char currChar, char nextChar, gameConfig::eKeys key)
{
	if (currChar == 'H')
	{
		if (nextChar == 'H' || ((nextChar == '<' || nextChar == '>' || nextChar == '=') && key == gameConfig::eKeys::UP))
		{
			return true;
		}
	}
	else
	{
		if (isOnFloor() && myMario.getBoard()->getChar(myMario.getX(), myMario.getY() + 2) == 'H' && key == gameConfig::eKeys::DOWN)
		{
			return true;
		}
	}
	return false;
}

bool mario::isFalling(char currChar, char nextChar, gameConfig::eKeys key)
{
	if (currChar == ' ')
	{
		if (isOnFloor() == false)
		{
			return true;
		}
	}
	return false;
}

bool mario::isJumping(char currChar, char nextChar, gameConfig::eKeys key)
{
	if ((currChar == ' ' && isOnFloor() && key == gameConfig::eKeys::UP) || jumping == true)
	{
		jumping = true;
		return true;
	}
	else
		return false;
}

point::States mario::findState(char currChar, char nextChar, gameConfig::eKeys key)
{
	if (isClimbing(currChar, nextChar, key))
		return point::States::CLIMBING;

	else if (isJumping(currChar, nextChar, key))
		return point::States::JUMPING;
			
	else if (isFalling(currChar, nextChar, key))
		return point::States::FALLING;
	else
		return point::States::WALKING_OR_STAYING;
	}

 void mario::jump(gameConfig::eKeys& key, char nextChar)
 {
 	if (heightJumping >= 2 || myMario.isFloor(nextChar))
 	{
 		isUp = false;
		if (myMario.getDiffX() == 0)
		{
			key = gameConfig::eKeys::STAY;
		}
		else if (myMario.getDiffX() == 1)
		{
			key = gameConfig::eKeys::RIGHT;
		}
		else
		{
			key = gameConfig::eKeys::LEFT;
		}
 	}

 	if (isUp)
 	{
 		if (heightJumping == 0 || heightJumping == 1)
 		{
			myMario.move(myMario.getDiffX(), -1);
 			heightJumping++;
 		}
 	}

 	else
 	{
 		if (heightJumping == 2 || heightJumping == 1)
 		{
			myMario.move(myMario.getDiffX(), 1);
 			heightJumping--;
 		}
 		else if (heightJumping == 0)
 		{
 			jumping = false;
 			isUp = true;
 		}
 	}
 }

 void mario::climbing(char nextChar, gameConfig::eKeys& key)
 {
	 heightJumping = 0;
	 jumping = false;
	 if (key == gameConfig::eKeys::UP)
	 {
		 if (nextChar == '<' || nextChar == '>' || nextChar == '=')
		 {
			 myMario.move(0, -2);
			 key = gameConfig::eKeys::STAY;
		 }
		 else
		 {
			 myMario.move(0, -1);
		 }
	 }
	 else
	 {
		 if (nextChar == '<' || nextChar == '>' || nextChar == '=')
		 {
			 myMario.move(0, 2);
			 key = gameConfig::eKeys::STAY;
		 }
		 else
		 {
			 myMario.move(0, 1);
		 }
	 }
 }
