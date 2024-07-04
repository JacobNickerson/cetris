#include "next_tetromino_board.hpp"

void NextTetBoard::reset() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board_matrix[i][j]->deactivate();
        }
    }
}

Block* NextTetBoard::getBlock(int row, int colu) {
    return board_matrix[row][colu];
}

void NextTetBoard::activate(Tetromino* tetromino) {
    std::array<std::pair<int,int>, 4> rotation_offsets = tetromino->getRotationPositions();
    for (int i = 0; i < 4; i++) {
        board_matrix[2+rotation_offsets[i].first][1+rotation_offsets[i].second]->activate();
    }
}