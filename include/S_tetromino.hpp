#ifndef S_TETROMINO_HPP
#define S_TETROMINO_HPP

#include "tetromino.hpp"
#include <iostream>

class S_Tetromino : public Tetromino {
    public:
        S_Tetromino() : Tetromino() {
            colo = sf::Color(255,0,0);
            rotation_positions = {{
                { {{0,-1}, {0,0}, {-1,0}, {-1,1}} },
                { {{-1,0}, {0,0}, {0,1}, {1,1}} },
                { {{1,-1}, {1,0}, {0,0}, {0,1}} },
                { {{-1,-1}, {0,-1}, {0,0}, {1,0}} }
            }};
        }
        
};

#endif