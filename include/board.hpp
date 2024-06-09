#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>

#include "block.hpp"

static constexpr int BOARD_HEIGHT = 20;
static constexpr int BOARD_WIDTH = 10;

class Board {
    private:
        std::array<std::array<Block*, BOARD_WIDTH>, BOARD_HEIGHT> board_matrix = {};

    public:
        // Constructor
        Board() {
            for (int y = 0; y < BOARD_HEIGHT; y++) {
                for (int x = 0; x < BOARD_WIDTH; x++) {
                    board_matrix[y][x] = new Block(x,y);
                }
            }
        }

        // Deconstructor (deleter, even)
        ~Board() {
            for (int y = 0; y < BOARD_HEIGHT; y++) {
                for (int x = 0; x < BOARD_WIDTH; x++) {
                    delete board_matrix[y][x];
                }
            }
        }

        // Get a pointer to the block at the position x,y
        Block* getBlock(int x, int y); 

        // does what it says on the tin
        // y is row index position
        void removeRow(int y) {
            for (int i=0; i < BOARD_WIDTH; i++) {
                board_matrix[y][i]->deactivate();
            }
        }
};

#endif