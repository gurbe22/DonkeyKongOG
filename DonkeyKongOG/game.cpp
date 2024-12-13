#include "game.h"

void game::mainMenu()
{
    bool running = true;
	ShowConsoleCursor(false); // Hide the cursor

    while (running) {
        system("cls"); // Clear the screen
        cout << "Donkey Kong Game\n";
        cout << "----------------\n";
        cout << "1. Start a New Game\n";
        cout << "8. Instructions and Keys\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";

        char choice = _getch();

        switch (choice) {
        case '1':
            runGame();
            break;
        case '8':
            displayInstructions();
            break;
        case '9':
            running = false;
            break;
        default:
            cout << "Invalid choice. Try again!\n";
            Sleep(1000);
        }
    }
    system("cls"); // Clear the screen
    cout << "Exiting the game. Goodbye!\n";
}

// Function to run the game
void game::runGame() 
{
    Board b;
    mario mario;
    displayBoard(b);
    mario.setBoard(b);
    gameConfig::eKeys keyPressed = gameConfig::eKeys::STAY; // משתנה אמיתי להעברה לפונקציה move
    while (true) {

        if (_kbhit()) {
            int key = _getch();
            key = std::tolower(key);
            if (key == (int)gameConfig::eKeys::ESC) { // ESC key
                break;
            }
            keyPressed = (gameConfig::eKeys)key; // עדכון המשתנה
            
        }
        mario.moveMario(keyPressed);
    }
}

void game::displayInstructions()
{
	system("cls"); // Clear the screen
    cout << "Instructions:\n";
    cout << "Use the following keys to move Mario:\n";
    cout << "A/a - Move Left\n";
    cout << "D/d - Move Right\n";
    cout << "W/w - Jump\n";
    cout << "X/x - Move Down\n";
    cout << "S/s - Stay\n";
    cout << "Press any key to return to the menu...\n";
    _getch(); // Wait for key press
}

void game::displayBoard(Board& b)
{
    system("cls"); // Clear the screen
    b.reset();
    b.print();
}
