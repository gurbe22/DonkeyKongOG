#include "utils.h"
#include "GameConfig.h"

using namespace std;

// Moves the cursor to the specified x, y position
void gotoxy(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    cout.flush(); 
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

// Hides or shows the console cursor
void ShowConsoleCursor(bool showFlag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

// Clears the console screen
void clear_screen()
{
    system("cls");
}

int bendingDirX(const int posX)
{
    return  posX < GameConfig::GAME_WIDTH / 2 ? 1 : -1;
}

int bendingDirY(const int posY)
{
    return  posY < GameConfig::GAME_HEIGHT / 2 ? 1 : -1;
}

