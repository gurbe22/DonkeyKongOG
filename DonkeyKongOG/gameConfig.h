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
		HAMMER = 'p', // Use the hammer
        ESC = 27,     // Escape key for pause menu
        EXIT = '\r',  // Enter key for exiting
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
    // Constants representing various types of terrain or objects on the game board
    static constexpr char FLOOR = '=';
    static constexpr char LFLOOR = '<';
    static constexpr char RFLOOR = '>';
    static constexpr char LADDER = 'H';
    static constexpr char OPEN_SPACE = ' ';

    static constexpr char WITH_HAMMER = 'V';

};
#endif
