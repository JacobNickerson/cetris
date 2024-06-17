#include "I_tetromino.hpp"
#include "tetromino.hpp"

const std::array<std::array<std::pair<int, int>, 4>, 4> rotation_position = {{
        { {{0, -1}, {0, 0}, {0, 1}, {0, 2}} },
        { {{-1, 0}, {0, 0}, {1, 0}, {2, 0}} },
        { {{0, -2}, {0, -1}, {0, 0}, {0, 1}} },
        { {{-2, 0}, {-1, 0}, {0, 0}, {1, 0}} }
}};

void I_Tetromino::expandPivot(Board& board) {
    for (size_t i = 0; i < blocks.size(); i++) {
        int new_row = pivot->getRow() + rotation_positions[rotation][i].first;
        int new_col = pivot->getCol() + rotation_positions[rotation][i].second;
        blocks[i] = board.getBlock(new_row, new_col);
    }
}

void I_Tetromino::expandPivot(int new_rotation, std::array<Block*, 4>& new_blocks, Board& board) {
    for (size_t i = 0; i < new_blocks.size(); i++) {
        int new_row = pivot->getRow() + rotation_positions[new_rotation][i].first;
        int new_col = pivot->getCol() + rotation_positions[new_rotation][i].second;
        new_blocks[i] = board.getBlock(new_row, new_col);
    }
}