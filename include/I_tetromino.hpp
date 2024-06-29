#ifndef I_TETROMINO_HPP
#define I_TETROMINO_HPP

#include "tetromino.hpp"
#include <iostream>

class I_Tetromino : public Tetromino {
    private:
        std::array<Block*, 4> blocks;
        Block* pivot;
        int rotation; 
        const sf::Color colo;
        const std::array<std::array<std::pair<int, int>, 4>, 4> rotation_positions = {{
            { {{0, -1}, {0, 0}, {0, 1}, {0, 2}} },
            { {{-1, 0}, {0, 0}, {1, 0}, {2, 0}} },
            { {{0, -2}, {0, -1}, {0, 0}, {0, 1}} },
            { {{-2, 0}, {-1, 0}, {0, 0}, {1, 0}} }
        }};
    
    public:
        I_Tetromino() : rotation(0), colo(sf::Color(255,0,255)) {
            for (size_t i = 0; i < blocks.size(); i++) {
                blocks[i] = nullptr;
            }
        };

        I_Tetromino(sf::Color colo) : rotation(0), colo(colo) {
            for (size_t i = 0; i < blocks.size(); i++) {
                blocks[i] = nullptr;
            }
        };

    
};

#endif