#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP
#include "Minesweeper.hpp"
#include <string>

// FileHandler class for save/load functionality
class FileHandler {
public:
    // Save the current game state to a file
    static void saveGame(const Minesweeper& game, const std::string& filename);

    // Load a game state from a file
    static void loadGame(Minesweeper& game, const std::string& filename);
};

#endif

