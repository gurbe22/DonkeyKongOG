#include "mario.h"
using namespace std;

char Mario::findNextChar(char currChar, GameConfig::eKeys key)
{
	// Get Mario's current position
	int x = myMario.getX();
	int y = myMario.getY();

	switch (key)
	{
	case GameConfig::eKeys::UP:
		if (currChar == GameConfig::LADDER)
		{
			// Reset horizontal movement when climbing a ladder
			myMario.setDiffX(0);
		}
		return myMario.getBoard()->getChar(x + myMario.getDiffX(), y - 1);
	case GameConfig::eKeys::DOWN:
		if (currChar == GameConfig::LADDER)
		{
			// Reset horizontal movement when climbing a ladder
			myMario.setDiffX(0);
		}
		return myMario.getBoard()->getChar(x + myMario.getDiffX(), y + 1);
	case GameConfig::eKeys::LEFT:
		// Get the character to the left of Mario
		return myMario.getBoard()->getChar(x - 1, y);
	case GameConfig::eKeys::RIGHT:
		// Get the character to the right of Mario
		return myMario.getBoard()->getChar(x + 1, y);
	case GameConfig::eKeys::STAY:
		// Get the character at Mario's current position
		return myMario.getBoard()->getChar(x, y);
	default:
		// Get the character in Mario's direction of movement
		int diffX = myMario.getDiffX();
		int diffY = myMario.getDiffY();
		return myMario.getBoard()->getChar(x + diffX, y + diffY);
	}
}

void Mario::moveMario(GameConfig::eKeys& key, vector <Enemy*>& enemies)
{
	// Variables for Mario's state and position
	Point::States state;
	char currChar = myMario.getBoard()->getChar(myMario.getX(), myMario.getY());
	char nextChar = findNextChar(currChar, key);

	if (currChar == GameConfig::HAMMER)
	{
		isHammer = true;
		myMario.getBoard()->setChar(myMario.getBoard()->getHammerStatusPositionX(), myMario.getBoard()->getHammerStatusPositionY(), GameConfig::WITH_HAMMER);
		gotoxy(myMario.getBoard()->getHammerStatusPositionX(), myMario.getBoard()->getHammerStatusPositionY());
		cout << GameConfig::WITH_HAMMER;
		gotoxy(myMario.getX(), myMario.getY());
	}

	// Determine Mario's state based on current and next characters
	state = findMarioState(currChar, nextChar, key);

	if (key == GameConfig::eKeys::RIGHT)
		setHammerDirection(GameConfig::directionPairs.at(GameConfig::directions::RIGHT).first);
	else if (key == GameConfig::eKeys::LEFT)
		setHammerDirection(GameConfig::directionPairs.at(GameConfig::directions::LEFT).first);

	if (key == GameConfig::eKeys::HAMMER && isHammer)
	{
		hammering(enemies);
	}

	switch (state)
	{
	case Point::States::FALLING:
		// Move Mario downward when falling
		myMario.move(0, 1);
		break;
	case Point::States::JUMPING:
		// Handle Mario's jumping mechanics
		jump(key, nextChar);
		break;
	case Point::States::CLIMBING:
		// Handle Mario's climbing mechanics
		climb(nextChar, key);
		myMario.setHeightFalling(0);
		break;
	case Point::States::WALKING_OR_STAYING:
		if (isAlive())
		{
			// Handle Mario's walking or staying behavior
			walkingOrStaying(key);
		}

		else
		{
			// Update falling state and decrement lives if Mario is not alive
			myMario.setHeightFalling(0);
			setLives();
		}
		break;

	}

	// Check if Mario is disqualified by barrels or other conditions
	if (isMarioDisqualified(enemies, nextChar))
	{
		setLives();
	}

	prevKey = key;

}

bool Mario::isClimbing(char currChar, char nextChar, GameConfig::eKeys key) const
{
	if (currChar == GameConfig::LADDER)
	{
		// Check if Mario can continue climbing
		if (nextChar == GameConfig::LADDER || ((nextChar == GameConfig::LFLOOR || nextChar == GameConfig::RFLOOR || nextChar == GameConfig::FLOOR)
			&& key == GameConfig::eKeys::UP || key == GameConfig::eKeys::STAY ||
			(key == GameConfig::eKeys::HAMMER && (prevKey == GameConfig::eKeys::STAY || prevKey == GameConfig::eKeys::UP))))
		{
			return true;
		}
	}
	else
	{
		// Check if Mario can start climbing downward from the floor
		char ch2Above = myMario.getBoard()->getChar(myMario.getX(), myMario.getY() + 2);
		if (myMario.isOnFloor() && ch2Above == GameConfig::LADDER && (key == GameConfig::eKeys::DOWN ||
			key == GameConfig::eKeys::HAMMER && prevKey == GameConfig::eKeys::DOWN))
		{
			return true;
		}
	}
	return false;
}

bool Mario::isJumping(char currChar, char nextChar, GameConfig::eKeys key)
{
	// Determine if Mario is jumping based on the environment and state
	if ((((currChar == GameConfig::OPEN_SPACE ||
		currChar == GameConfig::HAMMER) &&
		myMario.isOnFloor() &&
		key == GameConfig::eKeys::UP) ||
		jumping == true) && isAlive())
	{
		jumping = true;
		return true;
	}
	else
	{
		return false;
	}
}

Point::States Mario::findMarioState(char currChar, char nextChar, GameConfig::eKeys key)
{
	// Determine Mario's state based on climbing, jumping, or falling conditions
	if (isClimbing(currChar, nextChar, key))
		return Point::States::CLIMBING;
	else if (isJumping(currChar, nextChar, key))
		return Point::States::JUMPING;
	else if (myMario.isFalling(currChar))
		return Point::States::FALLING;
	else
		return Point::States::WALKING_OR_STAYING;
}

void Mario::jump(GameConfig::eKeys& key, char nextChar)
{
	// Handle upward jump mechanics
	if (heightJumping >= 2 || GameConfig::isFloor(nextChar))
	{
		isUp = false;
		// Adjust key for the next movement based on Mario's direction
		if (myMario.getDiffX() == 0)
			key = GameConfig::eKeys::STAY;
		else if (myMario.getDiffX() == 1)
			key = GameConfig::eKeys::RIGHT;
		else
			key = GameConfig::eKeys::LEFT;
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

void Mario::climb(char nextChar, GameConfig::eKeys& key)
{
	// Reset jumping state when climbing
	heightJumping = 0;
	jumping = false;

	if (key == GameConfig::eKeys::UP || (key == GameConfig::eKeys::HAMMER && prevKey == GameConfig::eKeys::UP))
	{
		// Move Mario upward when climbing
		if (nextChar == GameConfig::FLOOR || nextChar == GameConfig::LFLOOR || nextChar == GameConfig::RFLOOR)
		{
			myMario.move(0, -2);
			key = GameConfig::eKeys::STAY;
		}
		else
		{
			myMario.move(0, -1);
		}
	}
	else if (key == GameConfig::eKeys::DOWN || (key == GameConfig::eKeys::HAMMER && prevKey == GameConfig::eKeys::DOWN))
	{
		// Move Mario downward when climbing
		if (nextChar == GameConfig::FLOOR || nextChar == GameConfig::LFLOOR || nextChar == GameConfig::RFLOOR)
		{
			myMario.move(0, 2);
		}
		else
		{
			myMario.move(0, 1);
		}
	}
	else if (key == GameConfig::eKeys::STAY || (key == GameConfig::eKeys::HAMMER && prevKey == GameConfig::eKeys::STAY))
	{
		// Keep Mario in place
		myMario.move(0, 0);
	}
}

bool Mario::isAlive() const
{
	// Check if Mario is alive based on falling height
	return (myMario.getHeightFalling() < CHARS_TO_DEATH);
}

void Mario::hammering(vector<Enemy*>& enemies)
{
	for (auto it = enemies.begin(); it != enemies.end();)
	{
		Enemy* enemy = *it;
		if (abs(myMario.getX() + hammerDirection - enemy->getX()) <= 2 && abs(myMario.getY() - enemy->getY()) < 1)
		{
			if (dynamic_cast<SpecialGhost*>(enemy)) {
				addScore(SPECIAL_GHOST_SCORE);
			}
			else if (dynamic_cast<Barrel*>(enemy)) {
				addScore(BARREL_SCORE);
			}
			else if (dynamic_cast<Ghost*>(enemy))
			{
				addScore(GHOST_SCORE);
			}

			delete enemy;        // מחיקת האובייקט מהזיכרון
			it = enemies.erase(it); // מחיקת המצביע מהווקטור
		}
		else
		{
			++it; // מעבר לאובייקט הבא אם אין מחיקה
		}
	}
}

bool Mario::isMarioDisqualified(vector<Enemy*>& enemies, int nextChar) const
{
	int marioX = myMario.getX();
	int marioY = myMario.getY();
	int marioNextX = marioX + myMario.getDiffX();
	int marioNextY = marioY + myMario.getDiffY();

	for (auto& enemy : enemies) {
		int enemyX = enemy->getX();
		int enemyY = enemy->getY();
		int enemyNextX = enemyX + enemy->getDiffX();
		int enemyNextY = enemyY + enemy->getDiffY();

		// בדיקת התנגשות בהווה או בצעד הבא
		if (isCollision(marioX, marioY, marioNextX, marioNextY, enemyX, enemyY, enemyNextX, enemyNextY)) {
			return true;
		}

		// בדיקה אם מדובר בחבית והאם התפוצצה
		if (typeid(*enemy) == typeid(Barrel)) {
			if (enemy->getIsExplode() && isInExplosionRadius(marioX, marioY, enemyX, enemyY)) {
				return true;
			}
		}
	}

	// בדיקת אינטראקציה עם דונקי קונג
	if (nextChar == GameConfig::DONKEYKONG) {
		return true;
	}

	return false;
}

// פונקציה לבדוק אם יש התנגשות בין מרים לאויב
bool Mario::isCollision(int marioX, int marioY, int marioNextX, int marioNextY,
	int enemyX, int enemyY, int enemyNextX, int enemyNextY) const
{
	return (abs(marioX - enemyX) < 1 && abs(marioY - enemyY) < 1) ||
		(marioNextX == enemyNextX && marioNextY == enemyNextY) ||
		(marioNextX == enemyX && marioNextY == enemyY);
}

// פונקציה לבדוק אם המיקום של מרים נמצא בטווח הפיצוץ של החבית
bool Mario::isInExplosionRadius(int marioX, int marioY, int barrelX, int barrelY) const
{
	for (int dx = -2; dx <= 2; dx++) {
		for (int dy = -2; dy <= 2; dy++) {
			if (abs(dx) + abs(dy) <= 2) {
				if (marioX == barrelX + dx && marioY == barrelY + dy) {
					return true;
				}
			}
		}
	}
	return false;
}

bool Mario::isWon() const
{
	// Check if Mario reached Pauline
	if (myMario.getBoard()->getChar(myMario.getX(), myMario.getY()) == GameConfig::PAULINE)
	{
		return true;
	}
	return false;
}

void Mario::walkingOrStaying(GameConfig::eKeys key)
{
	// Handle Mario's walking or staying behavior based on the input key
	if (key == GameConfig::eKeys::LEFT || (key == GameConfig::eKeys::HAMMER && prevKey == GameConfig::eKeys::LEFT))
		myMario.move(-1, 0);
	else if (key == GameConfig::eKeys::RIGHT || (key == GameConfig::eKeys::HAMMER && prevKey == GameConfig::eKeys::RIGHT))
		myMario.move(1, 0);
	else if (key == GameConfig::eKeys::STAY || (key == GameConfig::eKeys::HAMMER && prevKey == GameConfig::eKeys::STAY))
		myMario.move(0, 0);
	else
	{
		// Continue movement based on direction
		int diffX = myMario.getDiffX();
		int diffY = myMario.getDiffY();
		myMario.move(diffX, diffY);
	}
}

void Mario::setHammerDirection() {
	hammerDirection = bendingDirX(myMario.getX());
}

void Mario::setHammerDirection(int dir) {
	hammerDirection = dir;
}

void Mario::addScore(int newPoints) {

	score = score + newPoints;
	if (score > GameConfig::MAX_SCORE)
	{
		score = GameConfig::MAX_SCORE;
	}
	myMario.getBoard()->addScore(score, myMario.getX(), myMario.getY());
}