#include "FileHandler.hpp"
#include <fstream>
#include <iostream>

void FileHandler::saveGame(const Minesweeper& game, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error: Could not open file for saving.\n";
        return;
    }
    
    outFile.close();
}

void FileHandler::loadGame(Minesweeper& game, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error: Could not open file for loading.\n";
        return;
    }

    // Load game
    // Read data 

    inFile.close();
}
