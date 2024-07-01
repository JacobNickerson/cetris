#ifndef Z_TETROMINO_HPP
#define Z_TETROMINO_HPP

#include "tetromino.hpp"
#include <iostream>

class Z_Tetromino : public Tetromino {
    public:
        Z_Tetromino() : Tetromino() {
            colo = sf::Color(0,255,0);
            rotation_positions = {{
                { {{-1,-1}, {-1,0}, {0,0}, {0,1}} },
                { {{1,0}, {0,0}, {0,1}, {-1,1}} },
                { {{0,-1}, {0,0}, {1,0}, {1,1}} },
                { {{1,-1}, {0,-1}, {0,0}, {-1,0}} }
            }};
        }
};

#endif