#include "O_tetromino.hpp"
#include "tetromino.hpp"


bool O_Tetromino::constructTetromino(Board& board) {
    std::array<Block*, 4> new_blocks = blocks;
    expandPivot(board);
    for (size_t i = 0; i < blocks.size(); i++) {
        if (blocks[i]->isActive()) {
            blocks = new_blocks;
            return false;
        }
    }
    return true;
}

bool O_Tetromino::rotateRight(Board& board) {
    return true;
}

bool O_Tetromino::rotateLeft(Board& board) {
    return true;
}

void O_Tetromino::expandPivot(Board& board) {
    blocks[0] = board.getBlock(pivot->getRow(), pivot->getColu());
    blocks[1] = board.getBlock(pivot->getRow()-1, pivot->getColu());
    blocks[2] = board.getBlock(pivot->getRow()-1, pivot->getColu()+1);
    blocks[3] = board.getBlock(pivot->getRow(), pivot->getColu()+1);
}

std::array<std::pair<int, int>, 4> O_Tetromino::getRotationPositions() {
    return {{
        {-1, 0}, {0, 0}, {0, 1}, {-1, 1}
    }};
}