#include "TheDonkyKongGame.h"

void TheDonkyKongGame::run() 
{
	ShowConsoleCursor(false);

	Board b;
	b.reset();
	b.print();

	mario mario;
	mario.setBoard(b);
	gameConfig::eKeys keyPressed = gameConfig::eKeys::STAY; // משתנה אמיתי להעברה לפונקציה move

	while (true)
	{
		if (_kbhit())
		{
			int key = _getch();
			key = std::tolower(key);

			if (key == (int)gameConfig::eKeys::ESC)
				break;

			keyPressed = (gameConfig::eKeys)key; // עדכון המשתנה
		}

		mario.draw('@');
		Sleep(500);
		mario.erase();

		mario.move(keyPressed); // העברת משתנה ולא ערך
	}
}
