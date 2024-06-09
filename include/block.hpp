#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <optional>

#include "color.hpp"

// Represents a block in the grid.
class Block {
    private:
        const int x; 
        const int y;
        std::optional<Color> col;

    public:
        // Constructor
        Block(int x, int y) : x(x), y(y) {};

        // "Activates" the block and assigns it a color.
        void activate(Color col);

        // Deactivates the block and removes its color.
        void deactivate();
};

#endif
