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

    // Dimensions of the game board
    static constexpr int GAME_WIDTH = 80;    // Board width
    static constexpr int GAME_HEIGHT = 25;   // Board height

    // Characters representing different entities in the game
    static constexpr char PAULINE = '$';    // Pauline character
    static constexpr char DONKEYKONG = '&'; // Donkey Kong character
    static constexpr char BARREL = 'O';     // Barrel character
    static constexpr char MARIO = '@';      // Mario character
    static constexpr char GHOST = 'x';      // Ghost character
    static constexpr char HAMMER = 'p';     // Hammer item

    // Characters representing terrain and obstacles
    static constexpr char LIMIT = 'Q';      // Limit
    static constexpr char FLOOR = '=';      // Flat floor
    static constexpr char LFLOOR = '<';     // Left-slanted floor
    static constexpr char RFLOOR = '>';     // Right-slanted floor
    static constexpr char LADDER = 'H';     // Ladder for climbing
    static constexpr char OPEN_SPACE = ' '; // Empty space
    static constexpr char INFO_POS = 'L';   // Legend top-left

    static constexpr char WITH_HAMMER = 'V'; // Legend: Mario holding a hammer

    static constexpr int MAX_SCORE = 9999;  // Maximum score

    // Utility function to check if a character is part of the floor
    static bool isFloor(char ch)
    {
        return ch == FLOOR ||
            ch == LFLOOR ||
            ch == RFLOOR ||
            ch == LIMIT;
    }
};
#endif
