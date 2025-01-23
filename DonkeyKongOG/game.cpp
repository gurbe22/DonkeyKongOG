#include "game.h"
using namespace std;

// Function to display the main menu
void Game::mainMenu()
{
	vector<std::string> fileNames;
	bool running = RUNNING;
	ShowConsoleCursor(false); // Hide the cursor
	getAllBoardFileNames(fileNames);
	sort(fileNames.begin(), fileNames.end());

	while (running) {
		system("cls"); // Clear the screen
		cin.clear();

		displayMenuWithAnimation(); // הצגת תפריט המשחק עם אנימציה

		// Get user input
		char choice = _getch();
		int levelChoice;

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
void Game::displayInstructions() const
{
	system("cls"); // Clear the screen
	cout << "---------------------------------------\n";
	cout << "            GAME INSTRUCTIONS          \n";
	cout << "---------------------------------------\n";
	cout << "Use the following keys to control Mario:\n";
	cout << "  A/a - Move Left\n";
	cout << "  D/d - Move Right\n";
	cout << "  W/w - Jump\n";
	cout << "  X/x - Move Down\n";
	cout << "  S/s - Stay\n";
	cout << "  P/p - Destroy a barrel or kill a ghost\n";
	cout << "---------------------------------------\n";
	cout << "Press any key to return to the menu...\n";
	_getch(); // Wait for user key press to return
}

// Function to display the board
void Game::displayBoard(Board& board, Mario& mario)
{
	system("cls"); // Clear the screen
	board.reset(); // Reset the board

	setLivesChar(board, mario);
	setScoreLine(board, mario);
	setLevelLine(board, mario);

	board.print(); // Print the board
}

void Game::setScoreLine(Board& board, Mario& mario)
{
	int score, scoreIdentation;
	score = mario.getScore();
	std::string strScore = std::to_string(score);
	scoreIdentation = board.getNewScoreIndetation(score);
	board.setLine(strScore, board.getScorePositionX() + scoreIdentation, board.getScorePositionY());
}

void Game::setLevelLine(Board& board, Mario& mario)
{
	std::string strLevel = std::to_string(level);
	board.setLine(strLevel, board.getLevelPositionX(), board.getLevelPositionY()); // Set number of lives on the board
}

void Game::setLivesChar(Board& board, Mario& mario)
{
	char livesChar = static_cast<char>('0' + mario.getLives()); // Convert integer to character representation
	board.setChar(board.getLivesPositionX(), board.getLivesPositionY(), livesChar); // Update the board with lives
}

int Game::displayLevelsChoices(vector<string>& fileNames) const {
	int size = fileNames.size();
	int currentPage = 0;
	string levelChoice;

	while (true) {
		system("cls"); // מנקה את המסך
		cout << "Choose a level to play:" << endl;

		// הדפסת השלבים בעמוד הנוכחי
		int start = currentPage * LEVELS_PER_PAGE;
		int end = min(start + LEVELS_PER_PAGE, size); // עד העמוד האחרון או סוף הרשימה
		for (int i = start; i < end; i++) {
			cout << i + 1 << ". " << fileNames[i] << endl;
		}

		// הודעה אם יש עמודים נוספים
		if (start + LEVELS_PER_PAGE < size) {
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
			if (start + LEVELS_PER_PAGE < size) {
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

void Game::displayMenuWithAnimation() const
{
	displayTitleWithAnimation();    // כותרת
	displayDonkyKongArtWithAnimation();      // אומנות ASCII
	displayOptionsWithAnimation();  // אפשרויות תפריט
}

void Game::displayTitleWithAnimation() const {
	std::vector<std::string> gameTitle = {
		" DDDDD   OOOOO   N   N  K   K   EEEEE   Y   Y    K   K    OOOOO  N   N  GGGG  ",
		" D    D O     O  NN  N  K  K    E        YYY     K  K    O     O NN  N  G     ",
		" D    D O     O  N N N  KKK     EEEE      Y      KKK    O       ON N N  G  GG ",
		" D    D O     O  N  NN  K  K    E         Y      K  K    O     O N  NN  G   G ",
		" DDDDD   OOOOO   N   N  K   K   EEEEE     Y      K   K    OOOOO  N   N  GGGG  ",
		""
	};
	printWithAnimation(gameTitle, ANIMATION_SPEED);
}

void Game::displayDonkyKongArtWithAnimation() const
{
	std::vector<std::string> donkyKongArt = {
		"      ,.-\" \"-. ,",
		"     /    ===   \\",
		"    /  =======   \\",
		"  __|  (0)   (0)  |__",
		" / _|    .---.    |_ \\",
		"|/.----/ O O \\----.\\ |",
		" \\/     |     |     \\/",
		" |    _________     |",
		" |   /         \\    |",
		" |   |  >---<  |    |",
		""
	};
	printWithAnimation(donkyKongArt, ANIMATION_SPEED);


	/*for (const auto& line : art) {
		int padding = (80 - line.length()) / 2;
		for (int i = 0; i < padding; ++i)
			std::cout << " ";
		std::cout << line << std::endl;
	}*/
	/************************  ASCII art generated with the help of ChatGPT ****************************/
}

// Function to set Mario's starting position
void Game::setMarioPos(Board& board, Mario& mario)
{
	mario.setStartingX(board.getMarioStartingX());
	mario.setStartingY(board.getMarioStartingY());
}

// Function to create all ghosts
void Game::createAllGhosts(vector<Ghost>& ghosts, Board board)
{
	std::vector<std::pair<int, int>> ghostPos = board.getGhostPos();
	int size = ghostPos.size();
	for (int i = 0; i < size; i++)
	{
		ghosts.push_back(Ghost(board, ghostPos[i].first, ghostPos[i].second));
	}
}

// Function to run the game
void Game::runGame(vector<std::string> fileNames, int levelChoice)
{
	system("cls"); // Clear the screen
	Board board;
	Mario mario;
	bool victory = false;
	level = 0;

	if (levelChoice > fileNames.size())
	{
		board.displayErrorNotExistFile();
		Sleep(5000);
		return;
	}
	if (fileNames.size() == 0)
	{
		board.displayErrorNoFiles();
		Sleep(5000);
		return;
	}

	for (const auto& filename : fileNames)
	{
		level++;
		if (levelChoice == 0 || levelChoice == level)
		{
			victory = false;

			board.resetGhostPos();

			if (!board.load(filename))
			{
				continue;
			}

			setMarioPos(board, mario);

			vector<Ghost> ghosts;
			vector<Barrel> barrels;

			barrels.reserve(10);

			int currentFrame;
			int barrelsX;
			int barrelsY = board.getDonkeyPosY();

			barrelsX = bendingDir(board.getDonkeyPosX()) + board.getDonkeyPosX();

			while (mario.getLives() > 0 && victory == false)
			{
				currentFrame = DELAY;
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
				GameConfig::eKeys keyPressed = GameConfig::eKeys::STAY;

				while (RUNNING)
				{
					// Initialize barrels with staggered delay
					if (currentFrame % DELAY == 0) {
						barrels.push_back(Barrel(board, barrelsX, barrelsY));
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
							if (key == (int)GameConfig::eKeys::EXIT)
							{
								// End game if exit is chosen
								mario.makeDeath();
								break;
							}
							else if (key == (int)GameConfig::eKeys::ESC)
							{
								// Reset and redisplay the board on resume
								board.reset();
								displayBoard(board, mario);
							}
							else if (key == (int)GameConfig::eKeys::SUICIDE)
							{
								mario.setLives();
								board.displayDisqualified();
								Sleep(2000);
								break;
							}
						}

						// Update the key pressed
						keyPressed = (GameConfig::eKeys)key;
					}

					// Move Mario based on the key pressed
					mario.moveMario(keyPressed, barrels, ghosts);
					// Check if Mario has won the game
					if (mario.isWon())
					{
						if (levelChoice == 0)
						{
							board.displayWonLevel();
							Sleep(5000);
						}
						victory = true;
						break;
					}

					// Draw Mario in his updated position
					mario.drawMario();

					moveEnemies(barrels, ghosts);
					// Add a delay for smooth gameplay
					Sleep(100);

					eraseAllCharacters(barrels, ghosts, mario);

					// Check if Mario lost a life
					if (lives != mario.getLives())
					{
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
		}
	}
	if (victory)
	{
		// Display the Victory screen
		board.displayVictory();
		Sleep(4000);
	}
	else
	{
		// Display the loss screen if Mario has no more lives
		board.displayLoss();
		Sleep(4000);
	}

}

void Game::moveEnemies(std::vector<Barrel>& barrels, std::vector<Ghost>& ghosts)
{
	moveBarrels(barrels);
	moveGhosts(ghosts);
}

void Game::eraseAllCharacters(vector<Barrel>& barrels, vector<Ghost>& ghosts, Mario& mario)
{
	mario.eraseMario();
	eraseBarrels(barrels);
	eraseGhosts(ghosts);
}

void Game::moveGhosts(vector<Ghost>& ghosts)
{
	for (auto& ghost : ghosts) {
		ghost.moveGhost(ghosts);
		ghost.draw();
	}
}

void Game::eraseGhosts(vector<Ghost>& ghosts)
{
	for (auto& ghost : ghosts) {
		ghost.erase();
	}
}

void Game::getAllBoardFileNames(std::vector<std::string>& vec_to_fill) {
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

void Game::printWithAnimation(const std::vector<std::string>& lines, int delayMs) const
{
	for (const auto& line : lines) {
		std::cout << line << std::endl;
		Sleep(delayMs); // עיכוב בין שורה לשורה
	}
}

void Game::displayOptionsWithAnimation() const
{
	std::vector<std::string> options = {
		"---------------------------------------",
		"               MAIN MENU               ",
		"---------------------------------------",
		"1. Start a new game",
		"2. Start a specific level",
		"8. Show instructions",
		"9. Exit the game",
		"---------------------------------------",
		"Enter your choice: "
	};
	printWithAnimation(options, ANIMATION_SPEED);
}

// Checks if the game is paused and handles pause state
bool Game::isPause(Board& board, int& key) const
{
	if (key == (int)GameConfig::eKeys::ESC)
	{
		board.displayPauseScreen(); // Display pause screen
		key = 0; // Reset key
		while (true)
		{
			key = _getch(); // Wait for key press
			key = tolower(key);

			if (key == (int)GameConfig::eKeys::ESC || key == (int)GameConfig::eKeys::EXIT || key == (int)GameConfig::eKeys::SUICIDE)
				break; // Exit if ESC or EXIT is pressed
		}

		return true;
	}
	return false;
}

// Erases the barrels from their positions
void Game::eraseBarrels(vector <Barrel>& barrels)
{
	for (auto& barrel : barrels) {
		barrel.erase();
	}
}

// Moves the barrels and handles their behaviors
void Game::moveBarrels(vector<Barrel>& barrels)
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
			it->draw(); // מציירים את החבית
			++it; // ממשיכים לאיטרטור הבא
		}
	}

}