#include "Minesweeper.hpp"
#include "Style.hpp"
#include <iostream>
#include <random>
#include <ctime>

//initialize the grid with given dimensions and number of mines
Minesweeper::Minesweeper(int width, int height, int mines)
    : gridWidth(width), gridHeight(height), mineCount(mines), totalCells(width* height),
    gameOver(false), winner(false) {
    initializeGrid( width,height);
    placeMines();
    calculateMines();
}

void Minesweeper::initializeGrid(int width, int height) {
    gridWidth = width;
    gridHeight = height;
    totalCells = width * height;
    grid = std::vector<Cell>(totalCells);
    remainingMines = mineCount; // Make sure to set the correct number of remaining mines if necessary
}


// Places mines random
void Minesweeper::placeMines() {
    std::mt19937 rng(std::time(nullptr));
    std::uniform_int_distribution<int> dist(0, totalCells - 1);

    for (int i = 0; i < mineCount; ++i) {
        int index;
        do {
            index = dist(rng);
        } while (grid[index].isMine);
        grid[index].isMine = true;
    }
}

// Calculate the number of adjacent mines for each cell

void Minesweeper::calculateMines() {
    for (int i = 0; i < totalCells; ++i) {
        if (!grid[i].isMine) {
            grid[i].adjacentMines = countMines(i);
        }
    }
}

// Count the number of mines adjacent to a given cell (at index)

int Minesweeper::countMines(int index) {
    int count = 0;
    int row = index / gridWidth;
    int col = index % gridWidth;

    // Iterate through neighboring cells

    for (int r = std::max(0, row - 1); r <= std::min(gridHeight - 1, row + 1); ++r) {
        for (int c = std::max(0, col - 1); c <= std::min(gridWidth - 1, col + 1); ++c) {
            if (r == row && c == col) continue;  // no check for this cell itself
            if (grid[r * gridWidth + c].isMine) ++count;  // Check if neighbor is a mine
        }
    }
    return count;
}

void Minesweeper::displayGrid() const {
    std::cout << "Remaining Mines: " << remainingMines << "\n\n";

    std::cout << "    "; // column labels
    for (char col = 'a'; col < 'a' + gridWidth; ++col) {
        std::cout << col << ' ';
    }
    std::cout << '\n';

    for (int row = 0; row < gridHeight; ++row) {
        std::cout << row << " | "; //  row labels
        for (int col = 0; col < gridWidth; ++col) {
            int index = row * gridWidth + col;
            if (grid[index].isRevealed) {
                if (grid[index].isMine) {
                    std::cout << MINE_SYMBOL;   // Display a mine
                }
                else if (grid[index].adjacentMines > 0) {
                    std::cout << grid[index].adjacentMines << ' ';  // number of adjacent mines
                }
                else {
                    std::cout << "  ";  //  empty space
                }
            }
            else {
                std::cout << (grid[index].isFlagged ? FLAG_SYMBOL : UNREVEALED_CELL) << ' ';  // Display flag or unrevealed cell
            }
        }
        std::cout << '\n';
    }
    
        
}
    

void Minesweeper::reveal(int row, int colIndex) {
   
    if (row < 0 || row >= gridHeight || colIndex < 0 || colIndex >= gridWidth) {
        std::cout << "Invalid cell coordinates.\n";
        return;
    }
    int index = row * gridWidth + colIndex;  // Calculate the index based on row and col

    if (grid[index].isRevealed) {
        std::cout << "Cell already revealed.\n";
        return;
    }

    grid[index].isRevealed = true;

    if (grid[index].isMine) {
        gameOver = true;
        winner = false;
        return;
        
    }
     if (grid[index].adjacentMines == 0) {
        revealCells(index);  // Reveal surrounding cells if no adjacent mines
    }
    if (checkWin()) {
        gameOver = true;
        winner = true;
    }
}

void Minesweeper::revealCells(int index) {
    int row = index / gridWidth;
    int col = index % gridWidth;

    for (int r = std::max(0, row - 1); r <= std::min(gridHeight - 1, row + 1); ++r) {
        for (int c = std::max(0, col - 1); c <= std::min(gridWidth - 1, col + 1); ++c) {
            int adjacentIndex = r * gridWidth + c;
            if (!grid[adjacentIndex].isRevealed && !grid[adjacentIndex].isMine) {
                grid[adjacentIndex].isRevealed = true;
                if (grid[adjacentIndex].adjacentMines == 0) {
                    revealCells(adjacentIndex);  // Recursively reveal
                }
            }
        }
    }
}
void Minesweeper::flag(int row, int colIndex) {
       
    int index = row * gridWidth + colIndex; 

    if (grid[index].isRevealed) {
        std::cout << "Cannot flag a revealed cell.\n";
        return;
    }

    grid[index].isFlagged = !grid[index].isFlagged;
    remainingMines += grid[index].isFlagged ? -1 : 1;
}
bool Minesweeper::checkWin() const {
    for (const Cell& cell : grid) {
        // If a non-mine cell is not revealed,  no win
        if (!cell.isMine && !cell.isRevealed) {
            return false;
        }
    }
    return true; // If all non-mine cells are revealed, win
}

int Minesweeper::getGridHeight() const {
    return gridHeight; // Return the height of the grid
}


int Minesweeper::getGridWidth() const {
    return gridWidth; // Return the width of the grid
}

int Minesweeper::getRemainingMines() const {
    return remainingMines;;
}



bool Minesweeper::isGameOver() const {
    return gameOver;
}


void Minesweeper::revealAllMines() {
    for (Cell& cell : grid) {
        if (cell.isMine) {
            cell.isRevealed = true;
        }
    }
}

bool Minesweeper::isWin() const {
    return winner;
}
Cell& Minesweeper::getCell(int row, int col) {
    return grid[row * gridWidth + col];
}
const std::vector<Cell>& Minesweeper::getGrid() const {
    return grid; 
}
void Minesweeper::setRemainingMines(int mines) {
    remainingMines = mines;
}
