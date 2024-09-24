//  This file contains the 'main' function. Program execution begins and ends there.


#include "GameController.hpp"
#include <iostream>

int main() {
    GameController gameController; // Create a GameController instance
    int choice;

    std::cout << "Welcome to Minesweeper!\n";
    std::cout << "Select an option:\n";
    std::cout << "1. Easy\n";
    std::cout << "2. Hard\n";
    std::cout << "3. Load Game\n";
    std::cin >> choice;

    // Start the game based on user choice
    gameController.startGame(choice);

    return 0; // End of the program
}
