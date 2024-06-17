#include "tetromino.hpp"

bool Tetromino::constructTetromino(Block* piv, Board& board) {}

// TType Tetromino::getType() {}

bool Tetromino::rotateRight(Board& board) {
    std::array<Block*, 4> new_blocks;
    int new_rotation;
    if (rotation == 3) {
        new_rotation = 0;
    } else {
        new_rotation = rotation+1;
    }
    expandPivot(new_rotation, new_blocks, board);
    for (Block* new_pBlock : new_blocks) {
        if (new_pBlock->isActive()) {
            for (size_t i = 0; i < new_blocks.size(); i++) {
                delete new_blocks[i];
                new_blocks[i] = nullptr;
            }
            return false;
        }
    }
    for (size_t i = 0; i < blocks.size(); i++) {
        blocks[i]->deactivate();
    }
    blocks = new_blocks;
    rotation = new_rotation;
    for (size_t i = 0; i < new_blocks.size(); i++) {
        new_blocks[i]->activate(colo);
        delete new_blocks[i];
        new_blocks[i] = nullptr;
    }
    return true;
    
}

bool Tetromino::rotateLeft(Board& board) {
    std::array<Block*, 4> new_blocks;
    int new_rotation;
    if (rotation == 0) {
        new_rotation = 3;
    } else {
        new_rotation = rotation-1;
    }
    expandPivot(new_rotation, new_blocks, board);
    for (Block* new_pBlock : new_blocks) {
        if (new_pBlock->isActive()) {
            for (size_t i = 0; i < new_blocks.size(); i++) {
                delete new_blocks[i];
                new_blocks[i] = nullptr;
            }
            return false;
        }
    }
    for (size_t i = 0; i < blocks.size(); i++) {
        blocks[i]->deactivate();
    }
    blocks = new_blocks;
    rotation = new_rotation;
    for (size_t i = 0; i < new_blocks.size(); i++) {
        new_blocks[i]->activate(colo);
        delete new_blocks[i];
        new_blocks[i] = nullptr;
    }
    return true;
    
}

bool Tetromino::up(Board& board) {
    // check for collisions
    for (Block* pBlock : blocks) {
        if (board.getBlock(pBlock->getRow(), pBlock->getCol()-1)->isActive()) {
            return false;
        }
    }
    // move all blocks
    for (Block* pBlock : blocks) {
        pBlock->deactivate();
        pBlock = board.getBlock(pBlock->getRow(), pBlock->getCol()-1);
        pBlock->activate(colo);
    }
    // move pivot
    movePivot(pivot->getRow(), pivot->getCol()-1, board);
    return true;
}

bool Tetromino::down(Board& board) {
    // check for collisions
    for (Block* pBlock : blocks) {
        if (board.getBlock(pBlock->getRow(), pBlock->getCol()+1)->isActive()) {
            return false;
        }
    }
    // move all blocks
    for (Block* pBlock : blocks) {
        pBlock->deactivate();
        pBlock = board.getBlock(pBlock->getRow(), pBlock->getCol()+1);
        pBlock->activate(colo);
    }
    // move pivot
    movePivot(pivot->getRow(), pivot->getCol()+1, board);
    return true;
}

bool Tetromino::left(Board& board) {
    // check for collisions
    for (Block* pBlock : blocks) {
        if (board.getBlock(pBlock->getRow()-1, pBlock->getCol())->isActive()) {
            return false;
        }
    }
    // move all blocks
    for (Block* pBlock : blocks) {
        pBlock->deactivate();
        pBlock = board.getBlock(pBlock->getRow()-1, pBlock->getCol());
        pBlock->activate(colo);
    }
    // move pivot
    movePivot(pivot->getRow()-1, pivot->getCol(), board);
    return true;
}

bool Tetromino::right(Board& board) {
    // check for collisions
    for (Block* pBlock : blocks) {
        if (board.getBlock(pBlock->getRow()+1, pBlock->getCol())->isActive()) {
            return false;
        }
    }
    // move all blocks
    for (Block* pBlock : blocks) {
        pBlock->deactivate();
        pBlock = board.getBlock(pBlock->getRow()+1, pBlock->getCol());
        pBlock->activate(colo);
    }
    // move pivot
    movePivot(pivot->getRow()+1, pivot->getCol(), board);
    return true;
}

bool Tetromino::hardDrop(Board& board) {
    int drop_dist = ghostPosition(board);
    if (drop_dist == 0) {
        return false;
    }
    for (size_t i = 0; i < blocks.size(); i++) {
        blocks[i]->deactivate();
        blocks[i] = board.getBlock(blocks[i]->getRow()+drop_dist, blocks[i]->getCol());
        blocks[i]->activate(colo);
    }
    pivot = board.getBlock(pivot->getRow()+drop_dist, pivot->getCol());
    return true;
}

int Tetromino::ghostPosition(Board& board) { // probably a faster way to do this
    int min_dist = 0;
    for (size_t i = 0; i < blocks.size(); i++) {
        int row_init = blocks[i]->getRow();
        int j = row_init;
        while (!board.getBlock(j, blocks[i]->getCol())) {
            j++;
        }
        min_dist = std::min(min_dist, j-row_init-1);
    }
    return min_dist;
}

void Tetromino::movePivot(int colu, int row, Board& board) {
    pivot = board.getBlock(colu, row);
}

void Tetromino::expandPivot(Board& board) {
    for (size_t i = 0; i < blocks.size(); i++) {
        int new_row = pivot->getRow() + rotation_positions[rotation][i].first;
        int new_col = pivot->getCol() + rotation_positions[rotation][i].second;
        blocks[i] = board.getBlock(new_row, new_col);
    }
}

void Tetromino::expandPivot(int new_rotation, std::array<Block*, 4>& new_blocks, Board& board) {
    for (size_t i = 0; i < new_blocks.size(); i++) {
        int new_row = pivot->getRow() + rotation_positions[new_rotation][i].first;
        int new_col = pivot->getCol() + rotation_positions[new_rotation][i].second;
        new_blocks[i] = board.getBlock(new_row, new_col);
    }
};