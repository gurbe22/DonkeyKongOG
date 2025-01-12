#include "mario.h"

char mario::findNextChar(char currChar, gameConfig::eKeys key)
{
	// Get Mario's current position
	int x = myMario.getX();
	int y = myMario.getY();

	switch (key)
	{
	case gameConfig::eKeys::UP:
		if (currChar == gameConfig::LADDER)
		{
			// Reset horizontal movement when climbing a ladder
			myMario.setDiffX(0);
		}
		return myMario.getBoard()->getChar(x + myMario.getDiffX(), y - 1);
	case gameConfig::eKeys::DOWN:
		if (currChar == gameConfig::LADDER)
		{
			// Reset horizontal movement when climbing a ladder
			myMario.setDiffX(0);
		}
		return myMario.getBoard()->getChar(x + myMario.getDiffX(), y + 1);
	case gameConfig::eKeys::LEFT:
		// Get the character to the left of Mario
		return myMario.getBoard()->getChar(x - 1, y);
	case gameConfig::eKeys::RIGHT:
		// Get the character to the right of Mario
		return myMario.getBoard()->getChar(x + 1, y);
	case gameConfig::eKeys::STAY:
		// Get the character at Mario's current position
		return myMario.getBoard()->getChar(x, y);
	default:
		// Get the character in Mario's direction of movement
		int diffX = myMario.getDiffX();
		int diffY = myMario.getDiffY();
		return myMario.getBoard()->getChar(x + diffX, y + diffY);
	}
}

void mario::moveMario(gameConfig::eKeys& key, vector <Barrel> &barrels)
{
	// Variables for Mario's state and position
	point::States state;
	char currChar = myMario.getBoard()->getChar(myMario.getX(), myMario.getY());
	char nextChar = findNextChar(currChar, key);

	// Determine Mario's state based on current and next characters
	state = findMarioState(currChar, nextChar, key);

	switch (state)
	{
	case point::States::FALLING:
		// Move Mario downward when falling
		myMario.move(0, 1);
		break;
	case point::States::JUMPING:
		// Handle Mario's jumping mechanics
		jump(key, nextChar);
		break;
	case point::States::CLIMBING:
		// Handle Mario's climbing mechanics
		climbing(nextChar, key);
		myMario.setHightFalling(0);
		break;
	case point::States::WALKING_OR_STAYING:
		if (isAlive())
		{
			// Handle Mario's walking or staying behavior
			WalkingOrStaying(key);
		}
		else
		{
			// Update falling state and decrement lives if Mario is not alive
			myMario.setHightFalling(0);
			setLives();
		}
		break;

	}

	// Check if Mario is disqualified by barrels or other conditions
	if (MarioIsDisqualified(barrels, nextChar)) 
	{
		setLives();
	}
}

bool mario::isClimbing(char currChar, char nextChar, gameConfig::eKeys key)
{
	if (currChar == gameConfig::LADDER)
	{
		// Check if Mario can continue climbing
		if (nextChar == gameConfig::LADDER || ((nextChar == gameConfig::LFLOOR || nextChar == gameConfig::RFLOOR || nextChar == gameConfig::FLOOR)
			&& key == gameConfig::eKeys::UP || key == gameConfig::eKeys::STAY))
		{
			return true;
		}
	}
	else
	{
		// Check if Mario can start climbing downward from the floor
		char ch2Above = myMario.getBoard()->getChar(myMario.getX(), myMario.getY() + 2);
		if (myMario.isOnFloor() && ch2Above == gameConfig::LADDER && key == gameConfig::eKeys::DOWN)
		{
			return true;
		}
	}
	return false;
}

bool mario::isJumping(char currChar, char nextChar, gameConfig::eKeys key)
{
	// Determine if Mario is jumping based on the environment and state
	if (((currChar == gameConfig::OPEN_SPACE && myMario.isOnFloor() && key == gameConfig::eKeys::UP) || jumping == true) && isAlive())
	{
		jumping = true;
		return true;
	}
	else
	{
		return false;
	}
}

point::States mario::findMarioState(char currChar, char nextChar, gameConfig::eKeys key)
{
	// Determine Mario's state based on climbing, jumping, or falling conditions
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
	// Handle upward jump mechanics
	if (heightJumping >= 2 || myMario.isFloor(nextChar))
	{
		isUp = false;
		// Adjust key for the next movement based on Mario's direction
		if (myMario.getDiffX() == 0)
			key = gameConfig::eKeys::STAY;
		else if (myMario.getDiffX() == 1)
			key = gameConfig::eKeys::RIGHT;
		else
			key = gameConfig::eKeys::LEFT;
	}

	if (isUp)
	{
		// Move Mario upward
		if (heightJumping == 0 || heightJumping == 1)
		{
			myMario.move(myMario.getDiffX(), -1);
			heightJumping++;
		}
	}
	else
	{
		// Move Mario downward after the jump peak
		if (heightJumping == 2 || heightJumping == 1)
		{
			myMario.move(myMario.getDiffX(), 1);
			heightJumping--;
		}
		else if (heightJumping == 0)
		{
			// Reset jump state
			jumping = false;
			isUp = true;
		}
	}
}

void mario::climbing(char nextChar, gameConfig::eKeys& key)
{
	// Reset jumping state when climbing
	heightJumping = 0;
	jumping = false;

	if (key == gameConfig::eKeys::UP)
	{
		// Move Mario upward when climbing
		if (nextChar == gameConfig::FLOOR || nextChar == gameConfig::LFLOOR || nextChar == gameConfig::RFLOOR)
		{
			myMario.move(0, -2);
			key = gameConfig::eKeys::STAY;
		}
		else
		{
			myMario.move(0, -1);
		}
	}
	else if (key == gameConfig::eKeys::DOWN)
	{
		// Move Mario downward when climbing
		if (nextChar == gameConfig::FLOOR || nextChar == gameConfig::LFLOOR || nextChar == gameConfig::RFLOOR)
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
		// Keep Mario in place
		myMario.move(0, 0);
	}
}

bool mario::isAlive()
{
	// Check if Mario is alive based on falling height
	return (myMario.getHeightFalling() < CHARS_TO_DEATH);
}

bool mario::MarioIsDisqualified(vector <Barrel> barrels, int nextChar)
{
	// Check for collision or proximity with barrels
	for (int i = 0; i < barrels.size(); i++)
	{
		int barrelX = barrels[i].getX();
		int barrelY = barrels[i].getY();
		int marioX = myMario.getX();
		int marioY = myMario.getY();

		if (abs(marioX - barrelX) < 1 && abs(marioY - barrelY) < 1)
		{
			return true;
		}
		if (barrels[i].getIsExplode())
		{
			// Check for explosion radius affecting Mario
			for (int dx = -2; dx <= 2; dx++)
			{
				for (int dy = -2; dy <= 2; dy++)
				{
					if (abs(dx) + abs(dy) <= 2)
					{
						if (marioX == barrelX + dx && marioY == barrelY + dy)
						{
							return true;
						}
					}
				}
			}
		}
	}
	// Check if Mario interacts with Donkey Kong
	if (nextChar == gameConfig::DONKEYKONG)
	{
		return true;
	}
	return false;
}

bool mario::isWon()
{
	// Check if Mario reached Pauline
	if (myMario.getBoard()->getChar(myMario.getX(), myMario.getY()) == gameConfig::PAULINE)
	{
		return true;
	}
	return false;
}

void mario::WalkingOrStaying(gameConfig::eKeys key)
{
	// Handle Mario's walking or staying behavior based on the input key
	if (key == gameConfig::eKeys::LEFT)
		myMario.move(-1, 0);
	else if (key == gameConfig::eKeys::RIGHT)
		myMario.move(1, 0);
	else if (key == gameConfig::eKeys::STAY)
		myMario.move(0, 0);
	else
	{
		// Continue movement based on direction
		int diffX = myMario.getDiffX();
		int diffY = myMario.getDiffY();
		myMario.move(diffX, diffY);
	}
}
