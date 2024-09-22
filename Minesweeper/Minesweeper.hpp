#ifndef MINESWEEPER_HPP
#define MINESWEEPER_HPP
#include <vector>
#include "Cell.hpp"

// The Minesweeper class manages the game board and  functionality
class Minesweeper {
private:
    std::vector<Cell> grid;      // The grid of cells
    int gridWidth, gridHeight;   // Dimensions of the grid
    int totalCells;              // Total number of cells
    int mineCount;               // Number of mines in the grid
    int remainingMines;          // Remaining unflagged mines
    bool gameOver;               
    bool winner;

    // Private functions
    void initializeGrid();
    void placeMines();
    void calculateMines();
    int  countMines(int index);
    void revealCells(int index);
 

public:
    Minesweeper(int width, int height, int mines);  // Constructor to initialize the game board
    void reveal(int row, int colIndex);  // Method to reveal a cell
    void flag(int row, int colIndex);    // Method to flag/unflag a cell
    bool checkWin();        // Check if the player has won
    void displayGrid();              // Display the grid
    int getGridHeight() const;       // Return the height of the grid
    int getGridWidth() const;        // Return the width of the grid
    bool isGameOver() const;         // Check if the game is over
    void revealAllMines();           // Reveal all mines on the grid
    bool isWin() const;
};

#endif 
