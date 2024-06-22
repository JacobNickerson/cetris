#include "board.hpp"


Block* Board::getBlock(int row, int colu) {
    return board_matrix[row][colu];
}

void Board::removeRow(int row) {
    for (int i=1; i < BOARD_WIDTH-1; i++) {
        board_matrix[row][i]->deactivate();
    }
}

bool Board::rowIsFull(int row) {
    for (int i = 1; i < BOARD_WIDTH-1; i++) {
        if (!board_matrix[row][i]->isActive()) {
            return false;
        }
    }
    return true;
}
