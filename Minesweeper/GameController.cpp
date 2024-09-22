#include "GameController.hpp"
#include "Minesweeper.hpp"
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
    char action; // Action chosen by the player (reveal or flag)
    int row;     // Row chosen by the player
    char col;    // Column chosen by the player

    // Prompt for the action
    std::cout << "Enter action (R for reveal, F for flag/unflag): ";
    std::cin >> action; // Read the action
   // std::cout << "You entered action: " << action << std::endl; // Debug output

    // Prompt for the row and column
    std::cout << "Enter row (0-" << (game->getGridHeight() - 1) << ") and column (a-"
        << (char)('a' + game->getGridWidth() - 1) << "): ";
    std::cin >> row >> col; // Read the row and column
    std::cout << "You entered row: " << row << " and column: " << col << std::endl; // Debug output

    // Validate input
    int colIndex = std::tolower(col) - 'a'; // Convert column letter to index
    //std::cout << "Column index calculated: " << colIndex << std::endl; // Debug output

    // Check for valid action
    if (action == 'R' || action == 'r') {
        if (row >= 0 && row < game->getGridHeight() && colIndex >= 0 && colIndex < game->getGridWidth()) {
            // std::cout << "Revealing cell (" << row << ", " << (char)('a' + colIndex) << ")" << std::endl; // Debug output
            game->reveal(row, colIndex); // Call the function to reveal the cell
        }
        else {
            std::cout << "Invalid coordinates. Try again.\n";
        }
    }
    else if (action == 'F' || action == 'f') {
        if (row >= 0 && row < game->getGridHeight() && colIndex >= 0 && colIndex < game->getGridWidth()) {
           // std::cout << "Flagging cell (" << row << ", " << colIndex << ")" << std::endl; // Debug output
            game->flag(row, colIndex); // Call the function to flag or unflag the cell
        }
        else {
            std::cout << "Invalid coordinates. Try again.\n";
        }
    }
    else {
        std::cout << "Invalid action. Try again.\n";
    }
}





