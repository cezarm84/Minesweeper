#include "GameController.hpp"
#include "Minesweeper.hpp"
#include "FileHandler.hpp"
#include <iostream>

// Constructor
GameController::GameController() : game(nullptr), gameOver(false) {}

// Starts the game with a chosen mode
void GameController::startGame(int mode) {
    int width, height, mines;
    bool playAgain = true;

    while (playAgain) {
        // Check if the mode is for loading a game
        if (mode == 3) {
            game = new Minesweeper(6, 6, 5);// create a game for the load function at game start
            std::string saveDirectory = "C:\\Users\\cezar\\source\\repos\\Minesweeper\\Minesweeper"; // directory where save files 
            std::vector<std::string> saveFiles = FileHandler::listSaveFiles(saveDirectory);

            if (saveFiles.empty()) {
                std::cout << "No saved games available to load.\n";
                continue; // Go back to the start to select difficulty or load again
            }
            else {
                std::cout << "Available saved games:\n";
                for (size_t i = 0; i < saveFiles.size(); ++i) {
                    std::cout << i + 1 << ". " << saveFiles[i] << "\n";
                }
                int fileChoice;
                std::cout << "Enter the number of the file you want to load: ";
                std::cin >> fileChoice;

                if (fileChoice > 0 && fileChoice <= saveFiles.size()) {
                    std::string filename = saveFiles[fileChoice - 1];
                    FileHandler::loadGame(*game, filename); // Load the game 

                    // Start the game loop with the loaded game
                    gameOver = false; // Reset game over status if needed
                    
                    // Game loop until the game over
                    while (!game->isGameOver()) {
                        game->displayGrid();
                        handleUserInput();         
                        if (gameOver) {
                            return; // Exit the function
                        }
                    }
                    if (game->isWin()) {
                        std::cout << "Congratulations! You've won the game!\n";
                    }
                    else {
                        std::cout << "Game Over! You hit a mine.\n";

                    }
                    // Game over, reveal all mines and display final state
                    game->revealAllMines();
                    game->displayGrid();
                    
                }
                else {
                    std::cout << "Invalid choice.\n";
                }

                continue; // Go back to the start to select difficulty or load again
            }
        }

        // Set game parameters based on difficulty mode
        if (mode == 1) { // Easy Mode
            width = 6;
            height = 6;
            mines = 5;
        }
        else if (mode == 2) { // Hard Mode
            width = 26;
            height = 10;
            mines = 30;
        }
        else {
            std::cout << "Please choose 1, 2, or 3.\n"; 
            std::cin >> mode;
            continue;
        }

        game = new Minesweeper(width, height, mines); // Create the game on heap
        gameOver = false;

        // Game loop until the game over
        while(!game->isGameOver()) {
            game->displayGrid();       // Display the current game state
            handleUserInput();         // Handle user input

            // Check for exit 
            if (gameOver) {
                return; // Exit the function
            }
        }

        // Game over, reveal all mines and display final state
        game->revealAllMines();
        game->displayGrid();

        if (game->isWin()) {
            std::cout << "Congratulations! You've won the game!\n";
        }
        else {
            std::cout << "Game Over! You hit a mine.\n";
        }

        delete game; // Free memory when the game ends

        // for play again
        char choice;
        std::cout << "Would you like to play again? (y/n): ";
        std::cin >> choice;
        if (std::tolower(choice) != 'y') {
            playAgain = false; // Exit the loop if no
        }
        else {
            std::cout << "Select difficulty:\n1. Easy\n2. Hard\n3. Load Game\n"; // Include load option
            std::cin >> mode; // Choose difficulty or load option again
        }
    }
}


// Handles user input for actions
void GameController::handleUserInput() {
    char action;
    int row;
    char col;
    bool validAction = false;

    while (!validAction) {
        std::cout << "Enter action (R for reveal, F for flag/unflag, S for save, L for load, E for exit): ";
        std::cin >> action;

        if (action == 'R' || action == 'r' || action == 'F' || action == 'f' || action == 'S' || action == 's' ||
            action == 'L' || action == 'l' || action == 'E' || action == 'e') {
            validAction = true;
        }
        else {
            std::cout << "Please enter 'R', 'F', 'S', 'L', or 'E'.\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    }

    if (action == 'S' || action == 's') {
        std::string filename;
        std::cout << "Enter filename: ";
        std::cin >> filename;
        filename += ".sav"; // add the .sav extension
        FileHandler::saveGame(*game, filename);
    }
    else if (action == 'L' || action == 'l') {
        std::string saveDirectory = "C:\\Users\\cezar\\source\\repos\\Minesweeper\\Minesweeper"; // directory where save files are located
        std::vector<std::string> saveFiles = FileHandler::listSaveFiles(saveDirectory); 

        if (saveFiles.empty()) {
            std::cout << "No saved games available to load.\n";
        }
        else {
            std::cout << "Available saved games:\n";
            for (size_t i = 0; i < saveFiles.size(); ++i) {
                std::cout << i + 1 << ". " << saveFiles[i] << "\n";
            }
            int fileChoice;
            std::cout << "Enter the number of the file you want to load: ";
            std::cin >> fileChoice;

            if (fileChoice > 0 && fileChoice <= saveFiles.size()) {
                std::string filename = saveFiles[fileChoice - 1];
                FileHandler::loadGame(*game, filename);
            }
            else {
                std::cout << "Invalid choice.\n";
            }
        }
    }
    else if (action == 'E' || action == 'e') {
        std::cout << "Exiting the game\n";
        gameOver = true;
        return;
        
    }
    else {
        bool validCoordinates = false;

        while (!validCoordinates) {
            std::cout << "Enter row (0-" << (game->getGridHeight() - 1) << ") and column (a-"
                << (char)('a' + game->getGridWidth() - 1) << "): ";
            std::cin >> row >> col;

            int colIndex = std::tolower(col) - 'a';

            if (row >= 0 && row < game->getGridHeight() && colIndex >= 0 && colIndex < game->getGridWidth()) {
                validCoordinates = true;
                if (action == 'R' || action == 'r') {
                    game->reveal(row, colIndex);
                }
                else if (action == 'F' || action == 'f') {
                    game->flag(row, colIndex);
                }
            }
            else {
                std::cout << "Invalid coordinates. Please try again.\n";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
        }
    }
}


