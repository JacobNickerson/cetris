#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <optional>

#include "color.hpp"

// Represents a block in the grid.
class Block {
    private:
        const int colu; 
        const int row;
        std::optional<Color> colo;

    public:
        // Constructor
        Block(int x, int y) : colu(x), row(y) {};

        // "Activates" the block and assigns it a color.
        void activate(Color colo);

        // Deactivates the block and removes its color.
        void deactivate();

        // returns x coord
        int getRow();

        // returns y coord
        int getCol();

        // returns exactly what you'd think
        bool isActive();
};

#endif