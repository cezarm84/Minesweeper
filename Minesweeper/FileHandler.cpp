#include "FileHandler.hpp"
#include <fstream>
#include <iostream>
#include <windows.h> 
#include <vector>
#include <string>

void FileHandler::saveGame(const Minesweeper& game, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error.\n";
        return;
    }

    // Save grid dimensions and number of mines
    outFile << game.getGridWidth() << " " << game.getGridHeight() << " " << game.getRemainingMines() << "\n";

    // Save each cell's state
    for (const auto& cell : game.getGrid()) {  
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
        std::cerr << "Error.\n";
        return ;
    }

    int width, height, remainingMines;
    inFile >> width >> height >> remainingMines;

    game.initializeGrid(width, height); 

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
    return;
}
// Function to list save files in a directory
std::vector<std::string> FileHandler::listSaveFiles(const std::string& directory) {
    std::vector<std::string> saveFiles;
    WIN32_FIND_DATA findFileData;
    std::wstring searchPath = stringToWstring(directory) + L"\\*.sav";

    HANDLE hFind = FindFirstFileW(searchPath.c_str(), &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "No save files found.\n";
        return saveFiles;
    }

    do {
        std::wstring fileName = findFileData.cFileName;
        saveFiles.push_back(wstringToString(fileName)); // Convert back to std::string
    } while (FindNextFileW(hFind, &findFileData) != 0);

    FindClose(hFind);
    return saveFiles;
}


std::string FileHandler::wstringToString(const std::wstring& wstr) {
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string str(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), &str[0], size_needed, NULL, NULL);
    return str;
}

// Function to convert std::string to std::wstring
std::wstring FileHandler::stringToWstring(const std::string& str) {
    return std::wstring(str.begin(), str.end());
}