#include "FileHandler.hpp"
#include <fstream>
#include <iostream>

void FileHandler::saveGame(const Minesweeper& game, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error: Could not open file for saving.\n";
        return;
    }

    // Save grid dimensions and number of mines
    outFile << game.getGridWidth() << " " << game.getGridHeight() << " " << game.getRemainingMines() << "\n";

    // Save each cell's state
    for (const auto& cell : game.getGrid()) { // Ensure getGrid returns a reference to the vector<Cell>
        outFile << cell.isMine << " "
            << cell.isRevealed << " "
            << cell.isFlagged << " "
            << cell.adjacentMines << "\n";
    }

    std::cout << "Game saved to " << filename << "\n";
}

void FileHandler::loadGame(Minesweeper& game, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error: Could not open file for loading.\n";
        return;
    }

    int width, height, remainingMines;
    inFile >> width >> height >> remainingMines;

    game.initializeGrid(width, height); // Ensure you have a method to initialize with dimensions

    // Load each cell's state
    for (int i = 0; i < width * height; ++i) {
        Cell cell;
        inFile >> cell.isMine
            >> cell.isRevealed
            >> cell.isFlagged
            >> cell.adjacentMines;

        // Set the loaded cell back into the grid
        game.getCell(i / width, i % width) = cell; // Use getCell to update the grid
    }

    game.setRemainingMines(remainingMines); // Set the remaining mines
    inFile.close();
    std::cout << "Game loaded from " << filename << "\n";
}

