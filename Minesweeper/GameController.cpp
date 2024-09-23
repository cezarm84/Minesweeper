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
        // Set game parameters based on difficulty mode
        if (mode == 1) { // Easy Mode
            width = 6;
            height = 6;
            mines = 5;
        }
        else { // Hard Mode
            width = 26;
            height = 10;
            mines = 30;
        }

        game = new Minesweeper(width, height, mines); // Create the game on heap
        gameOver = false;

        // Game loop until the game over
        while (!game->isGameOver()) {
            game->displayGrid();
            handleUserInput();
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
        std::cout << " do u like to play again? (y/n): ";
        std::cin >> choice;
        if (std::tolower(choice) != 'y') {
            playAgain = false; // Exit the loop if no
        }
        else {
            std::cout << "Select difficulty:\n1. Easy\n2. Hard\n";
            std::cin >> mode; //  choose difficulty again
        }
    }
}


// Handles user input for actions
void GameController::handleUserInput() {
    char action; // Action chosen by the player (reveal, flag, save, load)
    int row;     // Row chosen by the player
    char col;    // Column chosen by the player

    bool validAction = false; // Check if input action is valid

    // Loop until a valid action
    while (!validAction) {
        // Prompt for action
        std::cout << "Enter action (R for reveal, F for flag/unflag, S for save, L for load): ";
        std::cin >> action; // Read the action

        // Check for valid action
        if (action == 'R' || action == 'r' || action == 'F' || action == 'f' || action == 'S' || action == 's' || action == 'L' || action == 'l') {
            validAction = true; // Set to true if the action is valid
        }
        else {
            std::cout << "Please enter 'R', 'F', 'S', or 'L'.\n";
            std::cin.clear();   // Clear the error flag on cin
            std::cin.ignore(1000, '\n'); // Discard invalid input from the buffer
        }
    }

    if (action == 'S' || action == 's') {
        // Save the game
        std::string filename;
        std::cout << "Enter filename to save: ";
        std::cin >> filename;
        FileHandler::saveGame(*game, filename); // Use FileHandler to save the game
    }
    else if (action == 'L' || action == 'l') {
        // Load the game
        std::string filename;
        std::cout << "Enter filename to load: ";
        std::cin >> filename;
        FileHandler::loadGame(*game, filename); // Use FileHandler to load the game
    }
    else {
        // Handle regular actions (reveal/flag)
        bool validCoordinates = false; // Check if input coordinates are valid

        // Loop until valid coordinates are entered
        while (!validCoordinates) {
            // Prompt for the row and column
            std::cout << "Enter row (0-" << (game->getGridHeight() - 1) << ") and column (a-"
                << (char)('a' + game->getGridWidth() - 1) << "): ";
            std::cin >> row >> col; // Read the row and column

            int colIndex = std::tolower(col) - 'a'; // Convert column letter to index

            // Validate coordinates
            if (row >= 0 && row < game->getGridHeight() && colIndex >= 0 && colIndex < game->getGridWidth()) {
                validCoordinates = true; // Set to true if the coordinates are valid
                if (action == 'R' || action == 'r') {
                    game->reveal(row, colIndex); // Reveal the cell
                }
                else if (action == 'F' || action == 'f') {
                    game->flag(row, colIndex); // Flag or unflag the cell
                }
            }
            else {
                std::cout << "Invalid coordinates. Please try again.\n";
                std::cin.clear();   // Clear the error flag on cin
                std::cin.ignore(1000, '\n'); // Discard invalid input from the buffer
            }
        }
    }
}





