#include "board.hpp"


Block* Board::getBlock(int row, int colu) {
    return board_matrix[row][colu];
}

void Board::removeRow(int row) {
    for (int i=0; i < BOARD_WIDTH; i++) {
        board_matrix[row][i]->deactivate();
    }
}
