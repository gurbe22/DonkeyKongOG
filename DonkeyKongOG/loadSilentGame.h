#ifndef LOAD_SILENT_GAME_H
#define LOAD_SILENT_GAME_H

#include "loadGame.h"

class LoadSilentGame : public LoadGame
{
	void goToSleep() const override { Sleep(LOAD_SILENT_GAME_SPEED); }
public:
	LoadSilentGame() : LoadGame() {}
	~LoadSilentGame() {}
	void mainMenu() override;
};

#endif