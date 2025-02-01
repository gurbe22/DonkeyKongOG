#include "regularGame.h"
#include "saveGame.h"
#include "loadGame.h"
#include "loadSilentGame.h"
using namespace std;

int main(int argc, char** argv)
{
	Game* newGame = nullptr;
	if (argc == 1)
	{
		newGame = new RegularGame();
	}
	else if (argc == 2 && std::string(argv[1]) == "-load")
	{
		newGame = new LoadGame();
	}
	else if (argc == 3 && std::string(argv[1]) == "-load" && std::string(argv[2]) == "-silent")
	{
		newGame = new LoadSilentGame();
	}
	else if (argc == 2 && std::string(argv[1]) == "-save")
	{
		newGame = new SaveGame();
	}
	else
	{
		cout << "Invalid arguments" << endl;
		return 0;
	}
	newGame->mainMenu();
	delete newGame;
    return 0;
}