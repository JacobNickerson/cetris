#include "block.hpp"


int Block::getRow() {
    return row;
}

int Block::getColu() {
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

sf::Color Block::getColo() {
    if (colo.has_value()) {
        return colo.value();
    } else {
        return sf::Color(0,0,0);
    }
}