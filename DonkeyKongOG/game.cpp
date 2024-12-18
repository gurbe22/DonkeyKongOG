#include "game.h"

// Function to display the main menu
void game::mainMenu()
{
    bool running = RUNNING; 
	ShowConsoleCursor(false); // Hide the cursor

    while (running) {
        system("cls"); // Clear the screen

        //cout << "Donkey Kong Game\n";

        /***************************************From chatGPT*******************************************/
        std::cout << " DDDDD   OOOOO   N   N  K   K   EEEEE   Y   Y    K   K    OOOOO  N   N  GGGG  \n";
        std::cout << " D    D O     O  NN  N  K  K    E        YYY     K  K    O     O NN  N  G     \n";
        std::cout << " D    D O     O  N N N  KKK     EEEE      Y      KKK    O     O  N N N  G  GG \n";
        std::cout << " D    D O     O  N  NN  K  K    E         Y      K  K    O     O N  NN  G   G \n";
        std::cout << " DDDDD   OOOOO   N   N  K   K   EEEEE     Y      K   K   OOOOO   N   N  GGGG  \n\n";
        

        
        std::string art[] = {
        "    ,.-\" \"-.," ,
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
        /***************************************From chatGPT*******************************************/

        cout << "--------------------------------------------------------------------------------\n";
        cout << "1. Start a New Game\n";
        cout << "8. Instructions and Keys\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: \n";
        cout << "--------------------------------------------------------------------------------\n";

        char choice = _getch();

        switch (choice) {
        case START_GAME:
            runGame();
            break;
        case INSTRUCTIONS:
            displayInstructions();
            break;
        case EXIT_GAME:
            running = STOP_RUNNING;  
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
    while (mario.getLives() > 0)
    {
        mario.setMarioToStart();
        displayBoard(b , mario);
        mario.setBoard(b);
        int lives = mario.getLives();
        gameConfig::eKeys keyPressed = gameConfig::eKeys::STAY; 

        while (RUNNING) 
        {

            if (_kbhit())
            {
                int key = _getch();

                key = std::tolower(key);

                if (key == (int)gameConfig::eKeys::ESC)  // ESC key
                {
                    b.displayPauseScreen();  
                    key = 0;
                    while (true)
                    {
                        key = _getch();
                        //key = std::tolower(key);
                        if (key == (int)gameConfig::eKeys::ESC || key == (int)gameConfig::eKeys::EXIT)
                            break;
                    }
                }

                if (key == (int)gameConfig::eKeys::EXIT)
                { 
                    mario.makeDeath();
                    break;
                }
                else if (key == (int)gameConfig::eKeys::ESC)
                {
                    b.reset();
                    displayBoard(b, mario);
                }

                keyPressed = (gameConfig::eKeys)key; 
            
            }
            mario.moveMario(keyPressed);

            if (lives != mario.getLives()){
                //char numOfLives;
                //numOfLives = mario.getLives() + '0';
                //b.setChar(75, 1, numOfLives);
                //b.print();
                //Sleep(1000);
                break;
            }
        }
    }
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
    _getch(); // Wait for key press
}

// Function to display the board
void game::displayBoard(Board& b, mario& mario)
{
    char numOfLives;
    system("cls"); // Clear the screen
    b.reset();
    numOfLives = mario.getLives() + '0';
    b.setChar(75, 1, numOfLives);
    b.print();
}