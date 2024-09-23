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
    // void initializeGrid();
    void placeMines();
    void calculateMines();
    int  countMines(int index);
    void revealCells(int index);
 

public:
    Minesweeper(int width, int height, int mines);  // Constructor
    void reveal(int row, int colIndex);   // Reveal a cell
    void flag(int row, int colIndex);     // Flag/unflag a cell
    bool checkWin() const;                 // Check for win
    void displayGrid() const;              // Display the grid
    int getGridHeight() const;             // Get grid height
    int getGridWidth() const;              // Get grid width
    bool isGameOver() const;               // Check if game is over
    void revealAllMines();                 // Reveal all mines
    bool isWin() const;                    // Check if player has won
    int getRemainingMines() const;         // Get remaining mines
    void setRemainingMines(int mines);     // setter
    void initializeGrid(int width, int height);;                  // Initialize grid for loading
    Cell& getCell(int row, int col);       // Access a specific cell
    const std::vector<Cell>& getGrid() const;

};  


#endif 
