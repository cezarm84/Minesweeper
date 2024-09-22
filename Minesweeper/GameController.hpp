#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include "Minesweeper.hpp"

class GameController {
private:
    Minesweeper* game;  // Pointer to the current game
    bool gameOver;      //  if the game is over
    void handleUserInput();  // Handles user input for the game

public:
    GameController();   // Constructor

    void startGame(int mode);  // Starts a new game based on  mode

};
  
#endif 