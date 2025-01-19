#include "utils.h"
#include "gameConfig.h"

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

int bendingDir(const int posX)
{
    return  posX < gameConfig::GAME_WIDTH / 2 ? 1 : -1;
}
