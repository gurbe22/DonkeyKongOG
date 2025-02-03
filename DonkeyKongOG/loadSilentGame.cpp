#include "loadSilentGame.h"

// Main menu for silent load game
void LoadSilentGame::mainMenu()
{
	std::vector<std::string> fileNames;
	ShowConsoleCursor(false); // Hide the cursor
	getAllBoardFileNames(fileNames);
	sort(fileNames.begin(), fileNames.end());

	runGame(fileNames, 0,true); 
}