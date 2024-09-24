#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP
#include "Minesweeper.hpp"
#include <string>
#include <vector>

// FileHandler class for save/load functionality
class FileHandler {
public:
    // Save the current game state to a file
      static void saveGame(const Minesweeper& game, const std::string& filename);

    // Load a game state from a file
     static void loadGame(Minesweeper& game, const std::string& filename);

 
    static std::vector<std::string> listSaveFiles(const std::string& directory);

private:
    // Convert std::wstring to std::string
    static std::string wstringToString(const std::wstring& wstr);

    // Convert std::string to std::wstring
    static std::wstring stringToWstring(const std::string& str);
    
};

#endif

