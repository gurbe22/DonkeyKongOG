#ifndef GAMECONFIG_H
#define GAMECONFIG_H

class gameConfig
{
public:
    // Enumeration for key inputs used in the game
    enum class eKeys {
        LEFT = 'a',   // Move left
        RIGHT = 'd',  // Move right
        UP = 'w',     // Move up
        DOWN = 'x',   // Move down
        STAY = 's',   // Stay in the current position
        ESC = 27,     // Escape key for pause menu
        EXIT = '\r',  // Enter key for exiting
        NONE = '0'    // No key pressed
    };

    // Game board dimensions
    static constexpr int GAME_WIDTH = 80;   // Width of the game board
    static constexpr int GAME_HEIGHT = 25; // Height of the game board

    // Characters representing different entities in the game
    static constexpr char PAULINE = '$';    // Pauline character
    static constexpr char DONKEYKONG = '&'; // Donkey Kong character
    static constexpr char BARREL = 'O';     // Barrel character
    static constexpr char MARIO = '@';      // Mario character
    static constexpr char LIMIT = 'Q';      // Limit character
	static constexpr char INFO_POS = 'L';     // Indicating the legend top-left position, where Score and Remaining Live information shall be presented
    static constexpr char GHOST = 'x';      // Ghost
    static constexpr char HAMMER = 'p';      // Hammer



    // Number of barrels in the game
    static constexpr int NUM_OF_BARRELS = 12; // Total barrels
};
#endif
