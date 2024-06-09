#include "board.hpp"


Block* Board::getBlock(int x, int y) {
    return board_matrix[y][x];
};
