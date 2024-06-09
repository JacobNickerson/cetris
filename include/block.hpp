#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <optional>

#include "color.hpp"

class Block {
    public:
        int x;
        int y;
        Color col;

        // Constructor
        Block(int x, int y, Color col) : x(x), y(y), col(col) {};
};

typedef std::optional<Block> Cell;

#endif
