#ifndef STYLE_HPP
#define STYLE_HPP

// ANSI color codes for text styling

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"

// Symbols for Minesweeper

#define MINE_SYMBOL RED "M " RESET
#define FLAG_SYMBOL GREEN "F" RESET
#define UNREVEALED_CELL CYAN "*" RESET
#define EMPTY_CELL "  "  

#endif 