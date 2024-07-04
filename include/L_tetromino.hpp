#ifndef L_TETROMINO_HPP
#define L_TETROMINO_HPP

#include "tetromino.hpp"

class L_Tetromino : public Tetromino {
    public:
        L_Tetromino() : Tetromino() {
            colo = sf::Color(255,127,0);
            rotation_positions = {{
                { {{0,-1}, {0,0}, {0, 1}, {-1,1}} },
                { {{-1,0}, {0,0}, {1,0}, {1,1}} },
                { {{1,-1}, {0,-1}, {0,0}, {0,1}} },
                { {{-1,-1}, {-1,0}, {0,0}, {1,0}} },
            }};
        }
        
};

#endif