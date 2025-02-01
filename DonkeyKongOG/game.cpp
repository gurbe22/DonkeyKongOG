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

void Game::runGame(vector<std::string> fileNames, int levelChoice, bool isSilent)
{
	system("cls"); // Clear the screen
	Board board;
	Mario mario;
	bool victory = false;
	bool winLevel = false;
	level = 0;
	bool unmatching_result_found = false;

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
		size_t iteration = 0;
		Results results;
		Steps steps;
		long random_seed;

		std::string filename_prefix = filename.substr(0, filename.find_last_of('.'));
		std::string stepsFilename = filename_prefix + ".steps";
		std::string resultsFilename = filename_prefix + ".result";

		initializeGameData(stepsFilename, resultsFilename, random_seed, steps, results);

		srand(random_seed);
		level++;

		if (levelChoice == 0 || levelChoice == level)
		{
			victory = false;
			winLevel = false;
			board.resetGhostPos();

			if (!board.load(filename))
			{
				continue;
			}

			setMarioPos(board, mario);

			vector<Enemy*> enemies;

			enemies.reserve(10);

			int currentFrame;
			int barrelsX;
			int barrelsY = board.getDonkeyPosY();

			barrelsX = bendingDirX(board.getDonkeyPosX()) + board.getDonkeyPosX();
			size_t nextDisqualificationIteration = 0;

			while (mario.getLives() > 0 && winLevel == false)
			{
				currentFrame = DELAY;
				// Set Mario to his starting position at the beginning of each game
				mario.setMarioToStart();

				for (auto enemy : enemies) {
					delete enemy;
				}
				enemies.clear();

				// Display the game board with Mario at the starting position
				displayBoard(board, mario, isSilent); 

				// Create all ghosts
				createAllGhosts(enemies, board);

				// Link Mario to the game board
				mario.setBoard(board);

				// Store the current number of lives for comparison
				int lives = mario.getLives();

				// Initialize key press state to STAY
				GameConfig::eKeys keyPressed = GameConfig::eKeys::STAY;

				while (RUNNING)
				{
					++iteration;
					size_t  nextDisqualificationIteration = 0;
					validateResultsAndUpdateDisqualificationIteration(results, iteration, nextDisqualificationIteration, unmatching_result_found, filename);

					if (unmatching_result_found)
					{
						break;
					}

					// Initialize barrels with staggered delay
					if (currentFrame % DELAY == 0) {
						enemies.push_back(new Barrel(board, barrelsX, barrelsY));
					}
					currentFrame++;
					bool flag = false;
					// Check for user input

					flag = processGameInput(steps, results, iteration, board, mario, keyPressed);

					if (flag)
					{
						if (mario.getLives() > 0)
							handleDisqualification(nextDisqualificationIteration, unmatching_result_found, iteration, results, filename);
						break;
					}
					// Move Mario based on the key pressed
					mario.moveMario(keyPressed, enemies);
					// Check if Mario has won the game
					if (mario.isWon())
					{
						if (levelChoice == 0 && level < fileNames.capacity())
						{
							board.displayWonLevel();
							Sleep(5000);
							winLevel = true;
						}
						else
						{
							winLevel = true;
							victory = true;
						}

						break;
					}

					// Draw Mario in his updated position
					if (!isSilent)
					{
						mario.drawMario();
					}

					moveEnemies(enemies, isSilent);
					// Add a delay for smooth gameplay
					goToSleep();

					if (!isSilent)
					{
						eraseAllCharacters(enemies, mario);
					}

					// Check if Mario lost a life
					if (lives != mario.getLives())
					{
						if (mario.getLives() != 0)
						{
							handleDisqualification(nextDisqualificationIteration, unmatching_result_found, iteration, results, filename);
							// Display disqualification screen if a life is lost
							board.displayDisqualified();
							Sleep(2000);
						}

						break;
					}

					checkIfDisqualificationMatch(iteration, nextDisqualificationIteration, unmatching_result_found, filename);
				}

				if (unmatching_result_found)
				{
					break;
				}
			}

			handleGameResult(victory, winLevel, iteration, steps, results, stepsFilename, resultsFilename, unmatching_result_found, filename);
			if (mario.getLives() == 0)
				break;
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
		std::cout << " ";
	}
}

// Function to run the game


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

// Function to set Mario's starting position
void Game::setMarioPos(Board& board, Mario& mario)
{
	mario.setStartingX(board.getMarioStartingX());
	mario.setStartingY(board.getMarioStartingY());
}

void Game::setHammer(Board& board, Mario& mario)
{
	if (mario.getIsHammer())
	{
		board.setChar(board.getHammerStatusPositionX(), board.getHammerStatusPositionY(), GameConfig::WITH_HAMMER); // Set the hammer status on the board
		board.setChar(board.getHammerPositionX(), board.getHammerPositionY(), GameConfig::OPEN_SPACE); // Set the hammer on the board

	}
	else
	{
		board.setChar(board.getHammerStatusPositionX(), board.getHammerStatusPositionY(), GameConfig::WITHOUT_HAMMER); // Set the hammer status on the boardB

	}
}

// Function to create all ghosts
void Game::createAllGhosts(vector<Enemy*>& enemies, Board board)
{
	std::vector<std::pair<int, int>> ghostPos = board.getGhostPos();
	std::vector<std::pair<int, int>> specialGhostPos = board.getSpecialGhostPos();

	// עוברים על כל המיקומים ומוסיפים רוחות למערך
	for (const auto& pos : ghostPos)
	{
		// הקצאת אובייקט Ghost דינמית והוספה לווקטור כמצביע
		enemies.push_back(new Ghost(board, pos.first, pos.second));
	}

	// עוברים על כל המיקומים ומוסיפים רוחות למערך
	for (const auto& pos : specialGhostPos)
	{
		// הקצאת אובייקט Ghost דינמית והוספה לווקטור כמצביע
		enemies.push_back(new SpecialGhost(board, pos.first, pos.second));
	}
}

void Game::eraseAllCharacters(vector<Enemy*>& enemies, Mario& mario)
{
	mario.eraseMario();
	eraseEnemies(enemies);
}

void Game::eraseEnemies(vector<Enemy*>& enemies)
{
	for (auto& enemy : enemies) {
		enemy->erase();
	}
}

void Game::moveEnemies(vector<Enemy*>& enemies, bool isSilent)
{
	for (auto it = enemies.begin(); it != enemies.end();)
	{
		Enemy* enemy = *it;

		if (typeid(*enemy) == typeid(Ghost) || typeid(*enemy) == typeid(SpecialGhost))
		{
			enemy->move(enemies); // רוחות זזות (אם צריך שולחים רשימת רוחות)
			if (!isSilent)
			{
				enemy->draw();
			}
			++it; // עוברים לאובייקט הבא
		}
		else if (typeid(*enemy) == typeid(Barrel))
		{
			enemy->move();

			if (enemy->getIsExplode())
			{
				delete enemy; // מחיקת החבית מהזיכרון
				it = enemies.erase(it); // הסרת המצביע מהווקטור ועדכון האיטרטור
			}
			else
			{
				if (!isSilent)
				{
					enemy->draw();
				}
				++it; // עוברים לאובייקט הבא
			}
		}
		else
		{
			++it; // אם לא Ghost ולא Barrel, פשוט ממשיכים לאובייקט הבא
		}
	}
}

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
		" DDDDD   OOOOO   N   N  K   K   EEEEE     Y      K   K    OOOOO  N   N  GGGG  "
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

void Game::displayOptionsWithAnimation() const
{
	std::vector<std::string> options = {
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

void Game::printWithAnimation(const std::vector<std::string>& lines, int delayMs) const
{
	for (const auto& line : lines) {
		std::cout << line << std::endl;
		Sleep(delayMs); // עיכוב בין שורה לשורה
	}
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
void Game::displayBoard(Board& board, Mario& mario, bool isSilent)
{
	system("cls"); // Clear the screen
	board.reset(); // Reset the board

	setLivesChar(board, mario);
	setScoreLine(board, mario);
	setLevelLine(board, mario);
	setHammer(board, mario);
	if (!isSilent)
	{
		board.print(); // Print the board
	}
}

void Game::reportResultError(const std::string& message, const std::string& filename, size_t iteration) {
	system("cls");
	std::cout << "Screen " << filename << " - " << message << '\n';
	std::cout << "Iteration: " << iteration << '\n';
	std::cout << "Press any key to continue to next screens (if any)" << std::endl;
	_getch();
}
