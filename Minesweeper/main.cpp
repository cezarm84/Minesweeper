//  This file contains the 'main' function. Program execution begins and ends there.


#include "GameController.hpp"
#include <iostream>

int main() {
    GameController controller;
    int choice;

    std::cout << "Welcome to Minesweeper!\n";
    std::cout << "Select difficulty:\n";
    std::cout << "1. Easy\n";
    std::cout << "2. Hard\n";
    std::cin >> choice;

    controller.startGame(choice);  // Start the game with the selected mode

    return 0;
}
