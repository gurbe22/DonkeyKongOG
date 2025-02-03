#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <unordered_map>
#include <utility> // std::pair

// GameConfig holds constants and configurations used throughout the game.
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
        EXIT = 'm',   // Exit game
    };

    // Enum for movement directions
    enum class directions {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    // Mapping directions to (x, y) coordinate changes
    static const std::unordered_map<directions, std::pair<int, int>> directionPairs;

    // Game board dimensions
    static constexpr int GAME_WIDTH = 80;
    static constexpr int GAME_HEIGHT = 25;

    // Characters representing game entities
    static constexpr char PAULINE = '$';         // Goal character
    static constexpr char DONKEYKONG = '&';      // Enemy character
    static constexpr char BARREL = 'O';          // Rolling barrels
    static constexpr char MARIO = '@';           // Player character
    static constexpr char GHOST = 'x';           // Normal enemy
    static constexpr char SPECIAL_GHOST = 'X';   // Stronger ghost
    static constexpr char HAMMER = 'p';          // Hammer pickup

    // Characters representing terrain and obstacles
    static constexpr char LIMIT = 'Q';           // Game boundary
    static constexpr char FLOOR = '=';           // Walkable floor
    static constexpr char LFLOOR = '<';          // Left-slanted floor
    static constexpr char RFLOOR = '>';          // Right-slanted floor
    static constexpr char LADDER = 'H';          // Ladder for climbing
    static constexpr char OPEN_SPACE = ' ';      // Empty space
    static constexpr char INFO_POS = 'L';        // UI info position

    // Player hammer states
    static constexpr char WITH_HAMMER = 'V';
    static constexpr char WITHOUT_HAMMER = 'X';

    // Maximum score allowed in the game
    static constexpr int MAX_SCORE = 9999;

    // Display speed for animations (milliseconds)
    static constexpr int DISPLAY_SPEED = 3000;

    // Checks if the given character represents a floor
    static bool isFloor(char ch) {
        return ch == FLOOR || ch == LFLOOR || ch == RFLOOR || ch == LIMIT;
    }
};

#endif // GAME_CONFIG_H
