#ifndef I_TETROMINO_HPP
#define I_TETROMINO_HPP

#include "tetromino.hpp"
#include <iostream>

class I_Tetromino : public Tetromino {
    public:
        I_Tetromino() : Tetromino() {
            colo = sf::Color(0,255,255);
            rotation_positions = {{
                { {{0, -1}, {0, 0}, {0, 1}, {0, 2}} },
                { {{-1, 0}, {0, 0}, {1, 0}, {2, 0}} },
                { {{0, -2}, {0, -1}, {0, 0}, {0, 1}} },
                { {{-2, 0}, {-1, 0}, {0, 0}, {1, 0}} } 
            }};
        }

};

#endif