#ifndef CELL_HPP
#define CELL_HPP

// Defines the structure for each cell 
struct Cell {
    bool isMine = false;      // Indicates whether the cell contains a mine
    bool isRevealed = false;  // Indicates whether the cell has been revealed
    bool isFlagged = false;   // Indicates whether the cell has been flagged 
    int adjacentMines = 0;    // Stores the number of mines around this cell
};

#endif 