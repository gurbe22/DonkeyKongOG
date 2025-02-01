#include "loadSilentGame.h"

void LoadSilentGame::mainMenu()
{
	std::vector<std::string> fileNames;
	ShowConsoleCursor(false); // Hide the cursor
	getAllBoardFileNames(fileNames);
	sort(fileNames.begin(), fileNames.end());

	runGame(fileNames, 0,true); 
}