#ifndef ENEMY_H
#define ENEMY_H

#include "Point.h"

// Base class representing an enemy in the game
class Enemy
{
protected:
    Point myEnemy; // Position and movement logic for the enemy

    // Helper function to check if coordinates are within board boundaries
    bool isWithinBounds(int x, int y) const;

public:
    // Constructor initializes the enemy's position and assigns a board
    Enemy(Board& board, int enemyStartingX, int enemyStartingY)
        : myEnemy(enemyStartingX, enemyStartingY)
    {
        this->setBoard(board);
    }

    virtual ~Enemy() = default; // Virtual destructor for polymorphism

    // Set and retrieve the game board for the enemy
    void setBoard(Board& board) { myEnemy.setBoard(board); }
    Board* getBoard() const { return myEnemy.getBoard(); }

    // Position getters
    int getX() const { return myEnemy.getX(); }
    int getY() const { return myEnemy.getY(); }

    // Pure virtual function for drawing the enemy (must be implemented by derived classes)
    virtual void draw() const = 0;

    // Erases the enemy's current position from the board
    void erase() const { myEnemy.erase(); }

    // Movement behavior to be implemented by subclasses
    virtual void move(std::vector<Enemy*>& enemies) = 0;

    // Checks if the enemy has exploded (relevant for certain enemy types like barrels)
    virtual bool getIsExplode() const = 0;

    // Movement direction differences (for pathfinding or AI logic)
    int getDiffX() const { return myEnemy.getDiffX(); }
    int getDiffY() const { return myEnemy.getDiffY(); }

    // Direction change behavior (subclasses must define)
    virtual void changeDirectionX() = 0;
    virtual void changeDirectionY() = 0;
};

#endif
