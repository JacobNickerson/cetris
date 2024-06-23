#include "tetromino.hpp"
#include <iostream>

bool Tetromino::constructTetromino(Board& board) {
    std::array<Block*, 4> new_blocks = blocks;
    expandPivot(rotation, new_blocks, board);
    for (size_t i = 0; i < new_blocks.size(); i++) {
        if (new_blocks[i]->isActive()) {
            for (size_t j = 0; j < new_blocks.size(); j++) {
                delete new_blocks[j];
                new_blocks[j] = nullptr;
            }
            return false;
        }
    }
    
    for (size_t i = 0; i < new_blocks.size(); i++) {
        blocks[i] = board.getBlock(new_blocks[i]->getCol(), new_blocks[i]->getRow());
        delete new_blocks[i];
        new_blocks[i] = nullptr;
    }
    return true;
}

bool Tetromino::rotateRight(Board& board) {
    for (size_t i = 0; i < blocks.size(); i++) { // deactivate blocks to avoid collision detecting with itself
        blocks[i]->deactivate();
    }
    std::array<Block*, 4> new_blocks;
    int new_rotation = (rotation+1) % 4;
    expandPivot(new_rotation, new_blocks, board);
    for (Block* new_pBlock : new_blocks) {
        if (new_pBlock->isActive()) {
            activate();
            return false;
        }
    }
    for (size_t i = 0; i < blocks.size(); i++) {
        blocks[i] = board.getBlock(new_blocks[i]->getRow(), new_blocks[i]->getCol());
        blocks[i]->activate(colo);
    }
    rotation = new_rotation;

    return true;
    
}

bool Tetromino::rotateLeft(Board& board) {
    for (size_t i = 0; i < blocks.size(); i++) { // deactivate blocks to avoid collision detecting with itself
        blocks[i]->deactivate();
    }
    std::array<Block*, 4> new_blocks;
    int new_rotation = (rotation-1+4) % 4;
    expandPivot(new_rotation, new_blocks, board);
    for (Block* new_pBlock : new_blocks) {
        if (new_pBlock->isActive()) {
            activate();
            return false;
        }
    }
    for (size_t i = 0; i < blocks.size(); i++) {
        blocks[i] = board.getBlock(new_blocks[i]->getRow(), new_blocks[i]->getCol());
        blocks[i]->activate(colo);
    }
    rotation = new_rotation;

    return true;
    
}

bool Tetromino::up(Board& board) {
    deactivate();
    // check for collisions
    for (size_t i = 0; i < blocks.size(); i++) {
        if (board.getBlock(blocks[i]->getRow()-1, blocks[i]->getCol())->isActive()) {
            activate();
            return false;
        }
    }
    // move all blocks
    for (size_t i = 0; i < blocks.size(); i++) {
        blocks[i] = board.getBlock(blocks[i]->getRow()-1, blocks[i]->getCol());
        blocks[i]->activate(colo);
    }
    // move pivot
    movePivot(pivot->getRow()-1, pivot->getCol(), board);
    return true;
}

bool Tetromino::down(Board& board) {
    deactivate();
    // check for collisions
    for (size_t i = 0; i < blocks.size(); i++) {
        if (board.getBlock(blocks[i]->getRow()+1, blocks[i]->getCol())->isActive()) {
            activate();
            return false;
        }
    }
    // move all blocks
    for (size_t i = 0; i < blocks.size(); i++) {
        blocks[i] = board.getBlock(blocks[i]->getRow()+1, blocks[i]->getCol());
        blocks[i]->activate(colo);
    }
    // move pivot
    movePivot(pivot->getRow()+1, pivot->getCol(), board);
    return true;
}

bool Tetromino::left(Board& board) {
    // deactivate to prevent self collision
    deactivate();

    // check for collisions

    for (size_t i = 0; i < blocks.size(); i++) {
        if (board.getBlock(blocks[i]->getRow(), blocks[i]->getCol()-1)->isActive()) {
            activate();
            return false;
        }
    }
    // move all blocks
    for (size_t i = 0; i < blocks.size(); i++) {
        blocks[i] = board.getBlock(blocks[i]->getRow(), blocks[i]->getCol()-1);
        blocks[i]->activate(colo);
    }
    // move pivot
    movePivot(pivot->getRow(), pivot->getCol()-1, board);
    return true;
}

bool Tetromino::right(Board& board) {
    // deactivate to prevent self collision
    deactivate();

    // check for collisions

    for (size_t i = 0; i < blocks.size(); i++) {
        if (board.getBlock(blocks[i]->getRow(), blocks[i]->getCol()+1)->isActive()) {
            activate();
            return false;
        }
    }
    // move all blocks
    for (size_t i = 0; i < blocks.size() ; i++) {
        blocks[i] = board.getBlock(blocks[i]->getRow(), blocks[i]->getCol()+1);
        blocks[i]->activate(colo);
    }
    // move pivot
    movePivot(pivot->getRow(), pivot->getCol()+1, board);
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
}

void Tetromino::activate() {
    for (size_t i = 0; i < blocks.size(); i++) {
        blocks[i]->activate(colo);
    }
}

void Tetromino::deactivate() {
    for (size_t i = 0; i < blocks.size(); i++) {
        blocks[i]->deactivate();
    }
}

std::array<Block*, 4> Tetromino::getBlocks() {
    return blocks;
}

sf::Color Tetromino::getColor() {
    return colo;
}