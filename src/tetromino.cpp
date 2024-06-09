#include "tetromino.hpp"


bool Tetromino::right(Board& board) {
    std::array<Block*, 4> temp = blocks;
    
    for (int i = 0; blocks.size(); i++) {
        int new_x = blocks[i]->getX() + 1;
        int new_y = blocks[i]->getY();
        if (board.getBlock(new_x, new_y)->isActive()) {
            return false;
        }
    movePivot(pivot->getX()+1, pivot->getY());
    expandPivot();
    return true;
};

void Tetromino::expandPivot() {  // should this be a method of a subclass for each specific tetromino?
    return;                      // or should the type be a variable, and where do store the orientations anyway
};