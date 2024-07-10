#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <vector>
#include <algorithm>

#include "block.hpp"

// using std::find;

static constexpr int BOARD_HEIGHT = 24;
static constexpr int BOARD_WIDTH = 14;

class Board {
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
                board_matrix[r][1]->activate(sf::Color(0,0,0));
                board_matrix[r][BOARD_WIDTH-1]->activate(sf::Color(0,0,0));
                board_matrix[r][BOARD_WIDTH-2]->activate(sf::Color(0,0,0));
            }
            // activate floor
            for (int c = 0; c < BOARD_WIDTH; c++) {
                board_matrix[BOARD_HEIGHT-1][c]->activate(sf::Color(0,0,0));
                board_matrix[BOARD_HEIGHT-2][c]->activate(sf::Color(0,0,0));
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

        virtual void reset();

        // Get a pointer to the block at the position row, col : Board[row][col]
        virtual Block* getBlock(int row, int colu);

        // does what it says on the tin
        void removeRow(int row);

        // does what it says on the tin
        bool rowIsFull(int row);

        // checks tetromino placement for completed rows, removes completed rows
        // return an integer, 0 if no rows cleared otherwise returns points to add to score
        int checkPlacement(std::array<Block*, 4> blocks, int& game_level, int& game_clears, int& score);

        void pullBlocksDown(int& row);

    private:
        std::array<std::array<Block*, BOARD_WIDTH>, BOARD_HEIGHT> board_matrix = {};
};

#endif