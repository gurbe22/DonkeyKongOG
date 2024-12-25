#include "game.h"

using namespace std;

// Function to display the main menu
void game::mainMenu()
{
    bool running = RUNNING;
    ShowConsoleCursor(false); // Hide the cursor

    while (running) {
        system("cls"); // Clear the screen

        // Display the game title
        /************************  ASCII art generated with the help of ChatGPT ****************************/
        std::cout << " DDDDD   OOOOO   N   N  K   K   EEEEE   Y   Y    K   K    OOOOO  N   N  GGGG  \n";
        std::cout << " D    D O     O  NN  N  K  K    E        YYY     K  K    O     O NN  N  G     \n";
        std::cout << " D    D O     O  N N N  KKK     EEEE      Y      KKK    O     O  N N N  G  GG \n";
        std::cout << " D    D O     O  N  NN  K  K    E         Y      K  K    O     O N  NN  G   G \n";
        std::cout << " DDDDD   OOOOO   N   N  K   K   EEEEE     Y      K   K   OOOOO   N   N  GGGG  \n\n";

        // ASCII art for the game
        std::string art[] = {
            "    ,.-\" \"-. ,",
            "   /    ===   \\",
            "  /  =======   \\",
            "  __|  (0)   (0)  |__",
            " / _|    .---.    |_ \\",
            "|/.----/ O O \\----.\\ |",
            " \\/     |     |     \\/",
            " |   _________     |",
            " |  /         \\    |",
            " |  |  >---<  |    |",
        };

        for (const auto& line : art) {
            int padding = (80 - line.length()) / 2;
            for (int i = 0; i < padding; ++i)
                std::cout << " ";
            std::cout << line << std::endl;
        }
        /************************  ASCII art generated with the help of ChatGPT ****************************/

        // Display menu options
        cout << "--------------------------------------------------------------------------------\n";
        cout << "1. Start a New Game\n";
        cout << "8. Instructions and Keys\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: \n";
        cout << "--------------------------------------------------------------------------------\n";

        // Get user input
        char choice = _getch();

        switch (choice) {
        case START_NEW_GAME:
            runGame();  // Start a new game
            break;
        case SHOW_INSTRUCTIONS:
            displayInstructions();  // Show game instructions
            break;
        case EXIT_GAME:
            running = STOP_RUNNING;  // Exit the game
            break;
        default:
            cout << "Invalid choice. Try again!\n";
            Sleep(1000);
        }
    }
    system("cls"); // Clear the screen after exiting
    cout << "Exiting the game. Goodbye!\n";
}

// Function to display the instructions
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
    _getch(); // Wait for user key press to return
}

// Function to display the board
void game::displayBoard(Board& board, mario& mario)
{
    char numOfLives;
    system("cls"); // Clear the screen
    board.reset(); // Reset the board
    numOfLives = mario.getLives() + '0'; // Convert lives to char for display
    board.setChar(LIVES_POS_X, LIVES_POS_Y, numOfLives); // Set number of lives on the board
    board.print(); // Print the board
}

// Function to run the game
void game::runGame()
{
    Board board;
    mario mario;
    bool victory = false;

    while (mario.getLives() > 0 && victory == false)
    {
        // Set Mario to his starting position at the beginning of each game
        mario.setMarioToStart();

        // Display the game board with Mario at the starting position
        displayBoard(board, mario);

        // Link Mario to the game board
        mario.setBoard(board);

        // Store the current number of lives for comparison
        int lives = mario.getLives();

        // Initialize key press state to NONE
        gameConfig::eKeys keyPressed = gameConfig::eKeys::NONE;

        // Initialize barrels with staggered delay
        Barrel barrels[gameConfig::NUM_OF_BARRELS];
        int delay = 0;
        for (int i = 0; i < gameConfig::NUM_OF_BARRELS; i++)
        {
            barrels[i] = Barrel(delay);
            barrels[i].setBoard(board);
            delay += 30;
        }

        while (RUNNING)
        {
            // Check for user input
            if (_kbhit())
            {
                int key = _getch();

                key = std::tolower(key);

                // Handle pause functionality
                if (isPause(board, key))
                {
                    if (key == (int)gameConfig::eKeys::EXIT)
                    {
                        // End game if exit is chosen
                        mario.makeDeath();
                        break;
                    }
                    else if (key == (int)gameConfig::eKeys::ESC)
                    {
                        // Reset and redisplay the board on resume
                        board.reset();
                        displayBoard(board, mario);
                    }
                }

                // Update the key pressed
                keyPressed = (gameConfig::eKeys)key;
            }

            // Move Mario based on the key pressed
            mario.moveMario(keyPressed, barrels);

            // Check if Mario has won the game
            if (mario.isWon())
            {
                board.displayVictory();
                Sleep(5000);
                victory = true;
                break;
            }

            // Draw Mario in his updated position
            mario.drawMario();

            // Move barrels and update their positions
            moveBarrels(barrels, delay, board);

            // Add a delay for smooth gameplay
            Sleep(100);

            // Erase Mario from the previous position
            mario.eraseMario();

            // Erase barrels from the previous positions
            eraseBarrels(barrels);

            // Check if Mario lost a life
            if (lives != mario.getLives()) {
                if (mario.getLives() != 0)
                {
                    // Display disqualification screen if a life is lost
                    board.displayDisqualified();
                    Sleep(2000);
                }
                break;
            }


        }
    }
    if (victory == false)
    {
        // Display the loss screen if Mario has no more lives
        board.displayLoss();
        Sleep(5000);
    }
}

// Checks if the game is paused and handles pause state
bool game::isPause(Board& board, int& key)
{
    if (key == (int)gameConfig::eKeys::ESC)
    {
        board.displayPauseScreen(); // Display pause screen
		key = 0; // Reset key
        while (true)
        {
            key = _getch(); // Wait for key press
            if (key == (int)gameConfig::eKeys::ESC || key == (int)gameConfig::eKeys::EXIT)
                break; // Exit if ESC or EXIT is pressed
        }

        return true;
    }
    return false;
}

// Erases the barrels from their positions
void game::eraseBarrels(Barrel barrels[])
{
    for (int i = 0; i < gameConfig::NUM_OF_BARRELS; i++)
    {
        barrels[i].eraseBarrel(); // Erase the barrel
    }
}

// Moves the barrels and handles their behaviors
void game::moveBarrels(Barrel barrels[], int delay, Board board)
{
    for (int i = 0; i < gameConfig::NUM_OF_BARRELS; i++)
    {
        if (barrels[i].getIsExplode()) // If the barrel has exploded, reset it
        {
            barrels[i] = Barrel(delay);
            barrels[i].setBoard(board);

        }
        barrels[i].moveBarrel(); // Move the barrel
        barrels[i].drawBarrel(); // Draw the barrel
    }
}