#ifndef MARIO_H
#define MARIO_H

#include "point.h"
#include "gameConfig.h"
#include "barrel.h"
#include "ghost.h"
#include "specialGhost.h"
#include "enemy.h"

// The 'Mario' class manages the behavior and state of Mario in the game.
class Mario
{
    // Constants for Mario's initial state, scoring, and death conditions
    static constexpr int INITIAL_LIVES = 3;
    static constexpr int CHARS_TO_DEATH = 5;
    static constexpr int BARREL_SCORE = 50;
    static constexpr int GHOST_SCORE = 100;
    static constexpr int SPECIAL_GHOST_SCORE = 200;

    // Mario's attributes
    Point myMario;  // Represents Mario's position and movement
    int marioStartingX = 0; // Initial X position
    int marioStartingY = 0; // Initial Y position
    int heightJumping = 0;  // Tracks Mario's jump height
    bool jumping = false;   // True if Mario is jumping
    bool isUp = true;       // True if Mario is moving upwards in a jump
    int lives = INITIAL_LIVES; // Mario's remaining lives
    bool isHammer = false;  // True if Mario has a hammer
    int score = 0;          // Mario's current score
    int hammerDirection = 0;// Hammer attack direction
    GameConfig::eKeys prevKey = GameConfig::eKeys::STAY; // Last pressed key

    // Helper methods for movement and interactions
    void jump(GameConfig::eKeys& key, char nextChar);
    void climb(char nextChar, GameConfig::eKeys& key);
    void walkingOrStaying(GameConfig::eKeys key);
    void hammering(std::vector<Enemy*>& enemies);

    // Collision and state checks
    bool isClimbing(char currChar, char nextChar, GameConfig::eKeys key) const;
    bool isJumping(char currChar, char nextChar, GameConfig::eKeys key);
    bool isAlive() const;
    bool isMarioDisqualified(std::vector<Enemy*>& enemies, int nextChar) const;
    bool isCollision(int marioX, int marioY, int marioNextX, int marioNextY,
        int enemyX, int enemyY, int enemyNextX, int enemyNextY) const;
    bool isInExplosionRadius(int marioX, int marioY, int barrelX, int barrelY) const;

    // Determines Mario's next state based on movement
    char findNextChar(char currChar, GameConfig::eKeys key);
    Point::States findMarioState(char currChar, char nextChar, GameConfig::eKeys key);

public:
    // Constructor
    Mario() = default;

    // Rendering Mario on the board
    void drawMario() const {
        myMario.draw(GameConfig::MARIO);
    }

    // Removes Mario from the board
    void eraseMario() const {
        int x = myMario.getX();
        int y = myMario.getY();
        char currChar = myMario.getBoard()->getChar(x, y); // Get character at Mario's position

        if (currChar == GameConfig::HAMMER) {
            myMario.eraseCompletely();  // If standing on a hammer, erase everything
        }
        else {
            myMario.erase();
        }
    }

    // Mario's movement logic
    void moveMario(GameConfig::eKeys& key, std::vector<Enemy*>& enemies);
    void makeDeath() { lives = 0; } // Instantly sets Mario's lives to zero (used for game over)

    // State accessors
    int getLives() const { return lives; }
    int getScore() const { return score; }
    int getIsHammer() const { return isHammer; }
    bool isWon() const;  // Checks if Mario has won the level
    void addScore(int newPoints); // Increases Mario's score

    // Board interactions
    void setBoard(Board& board) { myMario.setBoard(board); }

    // Resets Mario to his starting position
    void setMarioToStart() {
        isHammer = false;
        jumping = false;
        myMario.setDiffX(0);
        myMario.setDiffY(0);
        myMario.setX(marioStartingX);
        myMario.setY(marioStartingY);
    }

    // Setters for Mario's starting position
    void setStartingX(int startingX) { marioStartingX = startingX; }
    void setStartingY(int startingY) { marioStartingY = startingY; }

    // Hammer direction control
    void setHammerDirection();
    void setHammerDirection(int dir);

    // Reduces Mario's life count
    void setLives() { lives--; }
};

#endif
