#ifndef LOAD_SILENT_GAME_H
#define LOAD_SILENT_GAME_H

#include "loadGame.h"

// 'LoadSilentGame' class extends 'LoadGame' to run the game in silent mode.
class LoadSilentGame : public LoadGame
{
    // Overrides sleep behavior to run the game instantly (no delay).
    void goToSleep() const override { Sleep(LOAD_SILENT_GAME_SPEED); }

public:
    LoadSilentGame() : LoadGame() {}  // Default constructor
    ~LoadSilentGame() {}              // Destructor

    // Runs the game in silent mode (overrides default menu behavior).
    void mainMenu() override;
};

#endif
