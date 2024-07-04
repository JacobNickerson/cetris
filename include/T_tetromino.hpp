#ifndef T_TETROMINO_HPP
#define T_TETROMINO_HPP

#include "tetromino.hpp"
#include <iostream>

class T_Tetromino : public Tetromino {
    public:
        T_Tetromino() : Tetromino() {
            colo = sf::Color(128,0,128);
            rotation_positions = {{
                { {{0,-1}, {0,0}, {-1,0}, {0,1}} },
                { {{-1,0}, {0,0}, {1,0}, {0,1}} },
                { {{0,-1}, {0,0}, {1,0}, {0,1}} },
                { {{-1,0}, {0,0}, {1,0}, {0,-1}} }
            }};
        }   
        
};

#endif