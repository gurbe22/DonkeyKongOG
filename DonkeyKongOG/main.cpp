#include "regularGame.h"
#include "saveGame.h"
#include "loadGame.h"
#include "loadSilentGame.h"
using namespace std;

int main(int argc, char** argv)
{
	Game* newGame = nullptr;
	if (argc == 1)	newGame = new RegularGame(); // Regular game (without saving the game)

	else if (argc == 2 && std::string(argv[1]) == "-load")	newGame = new LoadGame(); // Playing recorded game

	else if (argc == 3 && std::string(argv[1]) == "-load" && std::string(argv[2]) == "-silent")	 
		newGame = new LoadSilentGame(); // Playing recorded game in silent mode

	else if (argc == 2 && std::string(argv[1]) == "-save")	newGame = new SaveGame(); // Playing reguar game and record it

	else{
		cout << "Invalid arguments" << endl;
		return 0;
	}
	newGame->mainMenu();
	delete newGame;
    return 0;
}