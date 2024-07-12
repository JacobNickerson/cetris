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

        void pullBlocksDown(int& row);

        // takes the bottom row cleared out of a number of rows cleared in one move
        // scans all blocks above for connected segments, a segment is connected if it is connected to the rest of the blocks by active blocks
        // returns a vector of vector of pairs, each vector of pairs is a connected segment and their colors
        std::vector<std::vector<std::pair<Block*, sf::Color>>> findConnectedChunks(int row);

        // recursive function
        // given a row and col as parameters and a vector of pairs to add results into
        // if a block is active it is pushed into chunk and function is recursively called on neighboring blocks unless they are out of bounds
        // returns void but populates chunk vector with all blocks connected to the block in the initial function call and their current colors
        void floodFillChunk(int row, int col, std::vector<std::pair<Block*, sf::Color>>& chunk);

        // accepts a vector of pairs of block* and colors as a parameter, returns an int
        // integer is the distance from a chunk of connected blocks to the nearest active block
        int findGravityPosition(std::vector<std::pair<Block*, sf::Color>>& chunk);
        
        // accepts a vector of pairs of block* and colors and an integer as a parameter
        // activates all blocks in the chunk moved down by the integer
        // returns nothing, used as part of the sticky gravity methods
        void activateGravityChunk(std::vector<std::pair<Block*, sf::Color>>& chunk, int gravity_dist);

        // calls the above functions together, read their comments if you don't understand
        void stickyGravity(int row);

        void setUpDebug();

    private:
        std::array<std::array<Block*, BOARD_WIDTH>, BOARD_HEIGHT> board_matrix = {};
};

#endif