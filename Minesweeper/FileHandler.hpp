#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP
#include "Minesweeper.hpp"
#include <string>

//  class for save/load functionality
class FileHandler {
public:
    static void saveGame(const Minesweeper& game, const std::string& filename);

    static void loadGame(Minesweeper& game, const std::string& filename);
};

#endif 

