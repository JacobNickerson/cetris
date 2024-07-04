#ifndef O_TETROMINO_HPP
#define O_TETROMINO_HPP

#include "tetromino.hpp"

class O_Tetromino : public Tetromino {
    public:
        O_Tetromino() : Tetromino() {
            colo = sf::Color(255,255,0);
        }

        bool constructTetromino(Board& board) override;

        bool rotateRight(Board& board) override;

        bool rotateLeft(Board& board) override;

        void expandPivot(Board& board) override;

        std::array<std::pair<int, int>, 4> getRotationPositions() override;
};

#endif