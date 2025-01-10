#ifndef MARIO_H
#define MARIO_H

#include "point.h"
#include "gameConfig.h"
#include "barrel.h"

using namespace std;

// The 'mario' class manages the behavior and state of Mario in the game.
class mario
{
    // Constants for Mario's starting position, lives, and death criteria
    
    static constexpr int LIVES = 3;
    static constexpr int CHARS_TO_DEATH = 5;

    point myMario; // Represents Mario as a point on the board 
    int marioStartingX = 0;
    int marioStartingY = 0;
    int heightJumping = 0; // Tracks how high Mario is jumping
    bool jumping = false; // Indicates if Mario is currently jumping
    bool isUp = true; // Tracks the direction of Mario's jump
    int lives = LIVES; // Current number of lives Mario has

    // Function to make Mario jump
    void jump(gameConfig::eKeys& key, char nextChar);

    // Function to make Mario climb
    void climbing(char nextChar, gameConfig::eKeys& key);

    // Determines the next character based on Mario's position and input
    char findNextChar(char currChar, gameConfig::eKeys key);

    // Checks if Mario is in a climbing state
    bool isClimbing(char currChar, char nextChar, gameConfig::eKeys key);

    // Checks if Mario is in a jumping state
    bool isJumping(char currChar, char nextChar, gameConfig::eKeys key);

    // Handles Mario's walking or stationary behavior
    void WalkingOrStaying(gameConfig::eKeys key);

    // Determines Mario's current state based on the environment and input
    point::States findMarioState(char currChar, char nextChar, gameConfig::eKeys key);

    // Checks if Mario is alive
    bool isAlive();

    // Decrements Mario's life count
    void setLives()
    {
        lives--;
    }

    // Checks if Mario is disqualified due to interaction with barrels
    bool MarioIsDisqualified(vector <Barrel> barrels, int nextChar);

public:
    // Constructor to initialize Mario's starting position
    mario() : myMario() {};

    // Draws Mario on the board
    void drawMario() const
    {
        myMario.draw(gameConfig::MARIO);
    }

    // Erases Mario from the board
    void eraseMario() const
    {
        myMario.erase();
    }

    // Moves Mario based on the player's input and barrel interactions
    void moveMario(gameConfig::eKeys& key, vector <Barrel> &barrels);

    // Sets the game board for Mario's reference
    void setBoard(Board& board)
    {
        myMario.setBoard(board);
    }

    // Returns the number of lives Mario has left
    int getLives() const { return lives; }

    // Resets Mario to the starting position
    void setMarioToStart()
    {
        myMario.setX(marioStartingX);
        myMario.setY(marioStartingY);
    }

    // Sets Mario's lives to zero (indicates death)
    void makeDeath()
    {
        lives = 0;
    }

    // Checks if Mario has won the game
    bool isWon();

    void setStartingX(int startingX){ marioStartingX = startingX; }

    void setStartingY(int startingY){ marioStartingY = startingY; }
};

#endif