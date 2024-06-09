#include "board.hpp"


Board::Board(int x, int y) {
    width = x;
    height = y;
    for (int j = 0; j < y; j++) {
        for (int i = 0; i < x; i++) {
            Block temp(i, j);
            matrix.push_back(temp);
        }
    }
}

void Board::clearRow(int y) {
    int start = y * width;
    for (int i = y*width; i < (y+1)*width; i++) {
        // clear board[i]
    }
}

int Board::getIndex(int x, int y) {
    return width*x+height*y;
}