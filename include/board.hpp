#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>

#include "block.hpp"

static constexpr int BOARD_HEIGHT = 23;
static constexpr int BOARD_WIDTH = 12;

class Board {
    private:
        std::array<std::array<Block*, BOARD_WIDTH>, BOARD_HEIGHT> board_matrix = {};

    public:
        // Constructor
        Board() {
            // initialize entire board
            for (int r = 0; r < BOARD_HEIGHT; r++) {
                for (int c = 0; c < BOARD_WIDTH; c++) {
                    board_matrix[r][c] = new Block(c,r);
                }
            }
            // activate side walls
            for (int r = 0; r < BOARD_HEIGHT; r++) {
                board_matrix[r][0]->activate(sf::Color(0,0,0));
                board_matrix[r][BOARD_WIDTH-1]->activate(sf::Color(0,0,0));
            }
            // activate floor
            for (int c = 0; c < BOARD_WIDTH; c++) {
                board_matrix[BOARD_HEIGHT-1][c]->activate(sf::Color(0,0,0));
                // temp activate ceiling
                board_matrix[0][c]->activate(sf::Color(0,0,0));
            }
            
        }

        // Deconstructor (deleter, even)
        ~Board() {
            for (int r = 0; r < BOARD_HEIGHT; r++) {
                for (int c = 0; c < BOARD_WIDTH; c++) {
                    delete board_matrix[r][c];
                    board_matrix[r][c] = nullptr;
                }
            }
        }

        // Get a pointer to the block at the position row, col : Board[row][col]
        Block* getBlock(int row, int colu);


        // does what it says on the tin
        void removeRow(int row);

        // does what it says on the tin
        bool rowIsFull(int row);

        void reset();

};

#endif