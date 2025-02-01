#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <unordered_map>
#include <utility> // std::pair

struct GameConfig
{
    // Enumeration for key inputs used in the game
    enum class eKeys {
        LEFT = 'a',   // Move left
        RIGHT = 'd',  // Move right
        UP = 'w',     // Move up
        DOWN = 'x',   // Move down
        STAY = 's',   // Stay in the current position
        HAMMER = 'p', // Use the hammer
        SUICIDE = 'k',// Reset the level with one life less
        ESC = 27,     // Escape key for pause menu
        EXIT = '\r',  // Enter key for exiting
    };

    // Enum for movement directions
    enum class directions {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    // Mapping directions to (x, y) coordinates
    static const std::unordered_map<directions, std::pair<int, int>> directionPairs;

    // Dimensions of the game board
    static constexpr int GAME_WIDTH = 80;
    static constexpr int GAME_HEIGHT = 25;

    // Characters representing game entities
    static constexpr char PAULINE = '$';
    static constexpr char DONKEYKONG = '&';
    static constexpr char BARREL = 'O';
    static constexpr char MARIO = '@';
    static constexpr char GHOST = 'x';
    static constexpr char SPECIAL_GHOST = 'X';
    static constexpr char HAMMER = 'p';

    // Characters representing terrain and obstacles
    static constexpr char LIMIT = 'Q';
    static constexpr char FLOOR = '=';
    static constexpr char LFLOOR = '<';
    static constexpr char RFLOOR = '>';
    static constexpr char LADDER = 'H';
    static constexpr char OPEN_SPACE = ' ';
    static constexpr char INFO_POS = 'L';

    static constexpr char WITH_HAMMER = 'V';
    static constexpr char WITHOUT_HAMMER = 'X';

    static constexpr int MAX_SCORE = 9999;

    static constexpr int DISPLAY_SPEED = 3000;

    // Checks if the given character represents a floor
    static bool isFloor(char ch) {
        return ch == FLOOR || ch == LFLOOR || ch == RFLOOR || ch == LIMIT;
    }
};

#endif // GAME_CONFIG_H
