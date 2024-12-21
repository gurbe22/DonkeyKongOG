#include "mario.h"


char mario::findNextChar(char currChar, gameConfig::eKeys key)
{
	int x = myMario.getX();
	int y = myMario.getY();
	switch (key)
	{
	case gameConfig::eKeys::UP:
		if (currChar == point::LADDER)
		{
			myMario.setDiffX(0);
		}
		return myMario.getBoard()->getChar(x + myMario.getDiffX(), y - 1);
	case gameConfig::eKeys::DOWN:
		if (currChar == point::LADDER)
		{
			myMario.setDiffX(0);
		}
		return myMario.getBoard()->getChar(x + myMario.getDiffX(), y + 1);
	case gameConfig::eKeys::LEFT:
		return myMario.getBoard()->getChar(x - 1, y);
	case gameConfig::eKeys::RIGHT:
		return myMario.getBoard()->getChar(x + 1, y);
	default:
		return currChar;
	}
}

void mario::moveMario(gameConfig::eKeys& key, Barrel barrel[])
{

	point::States state; 
	char currChar, nextChar;

	currChar = myMario.getBoard()->getChar(myMario.getX(), myMario.getY()); 
	nextChar = findNextChar(currChar, key);
	state = findMarioState(currChar, nextChar, key);

	
	//else
	{
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
			myMario.setHightFalling(0);
			break;
		case point::States::WALKING_OR_STAYING:
			if (isAlive())
			{
				WalkingOrStaying(key);
			}
			else
			{
				myMario.setHightFalling(0);
				setLives();
			}
			break;
		}
	}
	if (MarioIsDisqualified(barrel, nextChar))
	{
		setLives();
	}
}

bool mario::isClimbing(char currChar, char nextChar, gameConfig::eKeys key)
{
	if (currChar == point::LADDER)
	{
		if (nextChar == point::LADDER || ((nextChar == point::LFLOOR || nextChar == point::RFLOOR || nextChar == point::FLOOR)
			&& key == gameConfig::eKeys::UP || key == gameConfig::eKeys::STAY))
		{
			return true;
		}
	}
	else
	{
		char ch2Above = myMario.getBoard()->getChar(myMario.getX(), myMario.getY() + 2);

		if (myMario.isOnFloor() && ch2Above == point::LADDER && key == gameConfig::eKeys::DOWN)
		{
			return true;
		}
	}
	return false;
}



bool mario::isJumping(char currChar, char nextChar, gameConfig::eKeys key)
{
	if ((currChar == point::OPEN_SPACE && myMario.isOnFloor() && key == gameConfig::eKeys::UP) || jumping == true)
	{
		jumping = true;
		return true;
	}
	else
		return false;
}

point::States mario::findMarioState(char currChar, char nextChar, gameConfig::eKeys key)
{
	if (isClimbing(currChar, nextChar, key))
		return point::States::CLIMBING;

	else if (isJumping(currChar, nextChar, key))
		return point::States::JUMPING;
			
	else if (myMario.isFalling(currChar))
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
		 if (nextChar == point::FLOOR || nextChar == point::LFLOOR || nextChar == point::RFLOOR)
		 {
			 myMario.move(0, -2);
			 key = gameConfig::eKeys::STAY;
		 }
		 else
		 {
			 myMario.move(0, -1);
		 }
	 }
	 else if(key == gameConfig::eKeys::DOWN)
	 {
		 if (nextChar == point::FLOOR || nextChar == point::LFLOOR || nextChar == point::RFLOOR)
		 {
			 myMario.move(0, 2);
		 }
		 else
		 {
			 myMario.move(0, 1);
		 }
	 }
	 else if (key == gameConfig::eKeys::STAY)
	 {
		 myMario.move(0, 0);
	 }
	
 }

 bool mario::isAlive()
 {
	 return (myMario.getHeightFalling() < CHARS_TO_DEATH); 
 }

 bool mario::MarioIsDisqualified(Barrel barrel[], int nextChar)
 {
	 for (int i = 0; i < gameConfig::NUM_OF_BARRELS; i++)
	 {
		 int barrelX = barrel[i].getX();
		 int barrelY = barrel[i].getY();

		 if (abs(myMario.getX() - barrelX) <= 1 && abs(myMario.getY() - barrelY) <= 1)
		 {
			 return true;
		 }
		 if (barrel[i].getIsExplode())
		 {
			 // לולאה לבדיקה ברדיוס 2 סביב מיקום החבית
			 for (int dx = -2; dx <= 2; dx++)
			 {
				 for (int dy = -2; dy <= 2; dy++)
				 {
					 // בדיקת רדיוס מרחק בין החבית למריו
					 if (abs(dx) + abs(dy) <= 2) // תנאי רדיוס 2
					 {
						 if (myMario.getX() == barrelX + dx && myMario.getY() == barrelY + dy)
						 {
							 return true; // מריו נמצא ברדיוס של פיצוץ החבית
						 }
					 }
				 }
			 }
		 }
	 }
	 if (nextChar == gameConfig::DONKEYKONG)
	 {
		 return true;
	 }
	 return false;
	 
 }

 bool mario::isWon()
 {
	 if (myMario.getBoard()->getChar(myMario.getX(), myMario.getY()) == gameConfig::PAULINE)
	 {
		 return true;
	 }
	 return false;
 }
