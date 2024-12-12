#include "TheDonkyKongGame.h"

void TheDonkyKongGame::run() 
{
	ShowConsoleCursor(false);

	Board b;
	mario mario;

	b.reset();
	b.print();

	mario.setBoard(b);
	gameConfig::eKeys keyPressed = gameConfig::eKeys::STAY; // ����� ����� ������ �������� move

	while (true)
	{
		if (_kbhit())
		{
			int key = _getch();
			key = std::tolower(key);

			if (key == (int)gameConfig::eKeys::ESC)
				break;

			keyPressed = (gameConfig::eKeys)key; // ����� ������
		}

		mario.draw('@');
		Sleep(100);
		mario.erase();
		mario.moveMario(keyPressed); // ����� ����� ��� ���
	}
}