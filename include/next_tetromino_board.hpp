#ifndef NEXT_TETROMINO_BOARD_HPP
#define NEXT_TETROMINO_BOARD_HPP

#include "board.hpp"
#include "tetromino.hpp"

class NextTetBoard : public Board {
    public:
        NextTetBoard() {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    board_matrix[i][j] = new Block(i, j);
                }
            }
        }
        
        ~NextTetBoard() {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    delete board_matrix[i][j];
                    board_matrix[i][j] = nullptr;
                }
            }
        }

        void reset() override;

        Block* getBlock(int row, int colu) override;

        void activate(Tetromino* tetromino);

    private:
        std::array<std::array<Block*, 4>, 4> board_matrix;
};


#endif