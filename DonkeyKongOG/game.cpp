#include "game.h"

using namespace std;

// Function to display the main menu
void game::mainMenu()
{
    vector<std::string> fileNames;
    bool running = RUNNING;
    ShowConsoleCursor(false); // Hide the cursor
    getAllBoardFileNames(fileNames);
    sort(fileNames.begin(), fileNames.end());

    while (running) {
        system("cls"); // Clear the screen
        cin.clear();

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
        cout << "2. Start a New Game with a specific level\n";
        cout << "8. Instructions and Keys\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: \n";
        cout << "--------------------------------------------------------------------------------\n";

        // Get user input
        char choice = _getch();
        char levelChoice = '0';

        switch (choice) {
        case START_NEW_GAME:
            runGame(fileNames);  // Start a new game
            break;
        case START_NEW_SPECIFC_LEVEL:
			levelChoice = displayLevelsChoices(fileNames);
            if (levelChoice == -1) {
                continue; // חזרה ללולאה
            }
            runGame(fileNames, levelChoice); // קריאה למשחק
            break;
        case SHOW_INSTRUCTIONS:
            displayInstructions();  // Show game instructions
            break;
        case EXIT_GAME:
            running = STOP_RUNNING;  // Exit the game
            break;
        default:
            cout << "Invalid choice. Please enter a valid option (1, 2, 8, 9).\n";
            Sleep(1000);
            break;
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
    board.setChar(board.getLivesPositionX(), board.getLivesPositionY(), numOfLives); // Set number of lives on the board
	board.setChar(board.getLevelPositionX(), board.getLevelPositionY(), level + '0'); // Set number of lives on the board
    board.print(); // Print the board
}

// Function to display the levels and get the user's choice
int game::displayLevelsChoices(vector<string>& fileNames) {
    int size = fileNames.size();
    int currentPage = 0;
    const int levelsPerPage = 2; // מספר שלבים בכל עמוד
    string levelChoice;

    while (true) {
        system("cls"); // מנקה את המסך
        cout << "Choose a level to play:" << endl;

        // הדפסת השלבים בעמוד הנוכחי
        int start = currentPage * levelsPerPage;
        int end = min(start + levelsPerPage, size); // עד העמוד האחרון או סוף הרשימה
        for (int i = start; i < end; i++) {
            cout << i + 1 << ". " << fileNames[i] << endl;
        }

        // הודעה אם יש עמודים נוספים
        if (start + levelsPerPage < size) {
            cout << "n. Next page\n";
        }
        if (currentPage > 0) {
            cout << "p. Previous page\n";
        }
        cout << "m. Return to main menu\n";
        cout << "Enter the level number and press Enter: ";

        cin >> levelChoice;
        
        // טיפול באפשרויות הקלט
        if (levelChoice == "m" || levelChoice == "M") {
            return -1; // חזרה לתפריט הראשי
        }
        if (levelChoice == "n" || levelChoice == "N") {
            if (start + levelsPerPage < size) {
                currentPage++; // מעבר לעמוד הבא
            }
            else {
                cout << "No more pages. Press any key to continue...\n";
                cin.ignore();
                Sleep(1500);
            }
            continue;
        }
        if (levelChoice == "p" || levelChoice == "P") {
            if (currentPage > 0) {
                currentPage--; // חזרה לעמוד הקודם
            }
            else {
                cout << "No previous page. Press any key to continue...\n";
                cin.ignore();
                Sleep(1500);
            }
            continue;
        }

        // בדיקה אם הקלט הוא מספר
        if (levelChoice[0] >= '1' && levelChoice[0] <= '9') {
            int choice = stoi(levelChoice);
            if (choice >= 1 && choice <= size) {
                return choice; // מחזיר את המספר המתאים באינדקס
            }
            else {
                cout << "Invalid choice. Please try again.\n";
                cin.ignore();
                Sleep(1500);
            }
        }
        else {
            cout << "Invalid input. Please try again.\n";
            cin.ignore();
            Sleep(1500);
        }
    }
}

// Function to set Mario's starting position
void game::setMarioPos(Board& board, mario& mario)
{
	mario.setStartingX(board.getMarioStartingX());
	mario.setStartingY(board.getMarioStartingY());
}

// Function to create all ghosts
void game::createAllGhosts(vector<ghost>& ghosts, Board board)
{
    std::vector<std::pair<int, int>> ghostPos = board.getGhostPos();
    int size = ghostPos.size();
	for (int i = 0; i < size; i++)
	{
		ghosts.push_back(ghost(board, ghostPos[i].first, ghostPos[i].second));
	}
}

// Function to run the game
void game::runGame(vector<std::string> fileNames, int levelChoice)
{
    system("cls"); // Clear the screen
    Board board;  
    mario mario;
    bool victory = false;
    level = 0;
    if (levelChoice > fileNames.size())
    {
        board.displayErrorNotExistFile();
        return;
    }
    if(fileNames.size() == 0)
    {
        board.displayErrorNoFiles();
        Sleep(5000);
        return;
    }
    else
    {
        for (const auto& filename : fileNames)
        {

            level++;

            if (levelChoice == 0 || levelChoice == level)
            {

                int x = 0, y = 0;

                victory = false;

                board.resetGhostPos();

                if (!board.load(filename))
                {
                    continue;
                }

                setMarioPos(board, mario);

                vector<ghost> ghosts;
                vector<Barrel> barrels;

                barrels.reserve(10);

                int delay = 30;
                int currentFrame;
                int barrelsX;
                int barrelsY = board.getDonkeyPosY();



                if (board.getDonkeyPosX() <= gameConfig::GAME_WIDTH / 2)
                    barrelsX = board.getDonkeyPosX() + 1;
                else
                    barrelsX = board.getDonkeyPosX() - 1;


                while (mario.getLives() > 0 && victory == false)
                {
                    currentFrame = 30;
                    // Set Mario to his starting position at the beginning of each game
                    mario.setMarioToStart();

                    barrels.clear();
                    ghosts.clear();
                    // Display the game board with Mario at the starting position
                    displayBoard(board, mario);

                    // Create all ghosts
                    createAllGhosts(ghosts, board);


                    // Link Mario to the game board
                    mario.setBoard(board);

                    // Store the current number of lives for comparison
                    int lives = mario.getLives();

                    // Initialize key press state to STAY
                    gameConfig::eKeys keyPressed = gameConfig::eKeys::STAY;

                    while (RUNNING)
                    {
                        // Initialize barrels with staggered delay
                        if (currentFrame % delay == 0) {
                            barrels.push_back(Barrel(barrelsX, barrelsY, board));
                        }
                        currentFrame++;

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
                        mario.moveMario(keyPressed, barrels, ghosts);

                        // Check if Mario has won the game
                        if (mario.isWon())
                        {
                            //board.displayVictory();
                            //Sleep(5000);
                            victory = true;
                            break;
                        }

                        // Draw Mario in his updated position
                        mario.drawMario();

                        // Move barrels and update their positions
                        moveBarrels(barrels);

                        moveGhosts(ghosts);

                        // Add a delay for smooth gameplay
                        Sleep(100);

                        // Erase Mario from the previous position
                        mario.eraseMario();

                        // Erase barrels from the previous positions
                        eraseBarrels(barrels);

                        eraseGhosts(ghosts);

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
                    Sleep(4000);
                    break;
                }
            }
            if (victory)
            {
                // Display the Victory screen
                board.displayVictory();
                Sleep(4000);
            }
        }
    }
    
}

void game::moveGhosts(vector<ghost>& ghosts)
{
    for (auto it = ghosts.begin(); it != ghosts.end(); )
    {
         it->moveGhost(ghosts); // מזיזים את הרוח
         it->drawGhost(); // מציירים את הרוח
         ++it; // ממשיכים לאיטרטור הבא
    }
}

void game::eraseGhosts(vector<ghost>& ghosts)
{
    for (int i = 0; i < ghosts.size(); i++)
    {
        ghosts[i].eraseGhost(); // Erase the ghost
    }
}

void game::getAllBoardFileNames(std::vector<std::string>& vec_to_fill) {
    namespace fs = std::filesystem;
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        auto filename = entry.path().filename();
        auto filenameStr = filename.string();
        if (filenameStr.substr(0, 6) == "dkong_" && filename.extension() == ".screen") {
            std::cout << " ^ added!!\n";
            vec_to_fill.push_back(filenameStr);
        }
    }
    if (vec_to_fill.size() == 0)
    {
        cout << " ";
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
void game::eraseBarrels(vector <Barrel> &barrels)
{
    for (int i = 0; i < barrels.size(); i++)
    {
        barrels[i].eraseBarrel(); // Erase the barrel
    }
}

// Moves the barrels and handles their behaviors
void game::moveBarrels(vector<Barrel> &barrels )
{
    for (auto it = barrels.begin(); it != barrels.end(); )
    {
        if (it->getIsExplode()) // אם החבית התפוצצה
        {
            it = barrels.erase(it); // מוחקים את החבית ומעדכנים את האיטרטור
        }
        else
        {
            it->moveBarrel(); // מזיזים את החבית
            it->drawBarrel(); // מציירים את החבית
            ++it; // ממשיכים לאיטרטור הבא
        }
    }

}