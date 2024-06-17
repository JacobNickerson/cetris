#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>

#include "block.hpp"

static constexpr int BOARD_HEIGHT = 22;
static constexpr int BOARD_WIDTH = 10;

class Board {
    private:
        std::array<std::array<Block*, BOARD_WIDTH>, BOARD_HEIGHT> board_matrix = {};

    public:
        // Constructor
        Board() {
            for (int r = 2; r < BOARD_HEIGHT; r++) {
                for (int c = 0; c < BOARD_WIDTH; c++) {
                    board_matrix[r][c] = new RoofBlock(c,r);
                }
            }
            for (int r = 2; r < BOARD_HEIGHT; r++) {
                for (int c = 0; c < BOARD_WIDTH; c++) {
                    board_matrix[r][c] = new Block(c,r);
                }
            }
        }

        // Deconstructor (deleter, even)
        ~Board() {
            for (int r = 0; r < BOARD_HEIGHT; r++) {
                for (int c = 0; c < BOARD_WIDTH; c++) {
                    delete board_matrix[r][c];
                }
            }
        }

        // Get a pointer to the block at the position row, col : Board[row][col]
        Block* getBlock(int row, int colu);


        // does what it says on the tin
        void removeRow(int row);

};

#endif