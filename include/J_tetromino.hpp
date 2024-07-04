#ifndef J_TETROMINO_HPP
#define J_TETROMINO_HPP

#include "tetromino.hpp"
#include <iostream>

class J_Tetromino : public Tetromino {
    public:
        J_Tetromino() : Tetromino() {
            colo = sf::Color(0,0,255);
            rotation_positions = {{
                { {{-1,-1}, {0,-1}, {0,0}, {0,1}} },
                { {{-1,1}, {-1,0}, {0,0}, {1,0}} },
                { {{0,-1}, {0,0}, {0,1}, {1,1}} },
                { {{-1,0}, {0,0}, {1,0}, {1,-1}} }
            }};
        }
        
};

#endif