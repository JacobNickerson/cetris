#include "block.hpp"


int Block::getX() {
    return x;
}

int Block::getY() {
    return y;
}

bool Block::isActive() {
    if (col.has_value()) return true;
    return false;
}

void Block::activate(Color color) {
    col = color;
}

void Block::deactivate() {
    col.reset();
}
