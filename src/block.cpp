#include "block.hpp"


int Block::getRow() {
    return row;
}

int Block::getCol() {
    return colu;
}

bool Block::isActive() {
    if (colo.has_value()) return true;
    return false;
}

void Block::activate(sf::Color new_color) {
    colo = new_color;
}

void Block::deactivate() {
    colo.reset();
}
