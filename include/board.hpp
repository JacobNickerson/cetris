#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "block.hpp"
#include "tetromino.hpp"


class Board {
    private:
        int width;
        int height;
        std::vector<Block> matrix;

    public:
        Board(int _width, int _height);

        // Clears one row from the board, board is 0 indexed
        void clearRow(int y);

        // Spawns a tetromino (duh)
        // Returns a bool, true if the tetromino is successfully spawned else false
        bool spawnTetromino(Tetromino);

        





};

#endif