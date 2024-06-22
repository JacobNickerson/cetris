#ifndef O_TETROMINO_HPP
#define O_TETROMINO_HPP

#include "tetromino.hpp"

class O_Tetromino : public Tetromino {
    private:
        std::array<Block*, 4> blocks;
        Block* pivot;
        int rotation; 
        sf::Color colo;
    
    public:

        bool rotateRight(Board& board);

        bool rotateLeft(Board& board);

        void expandPivot(Board& board);
};

#endif