#include "block.hpp"


int Block::getRow() {
    return row;
}

int Block::getColu() {
    return colu;
}

bool Block::isActive() {
    return active;
}

void Block::activate() {
    colo = sf::Color(255,255,255);
    active = true;
}

void Block::activate(sf::Color new_color) {
    colo = new_color;
    active = true;
}

void Block::deactivate() {
    active = false;
}

sf::Color Block::getColo() {
    if (colo.has_value()) {
        return colo.value();
    } else {
        return sf::Color(0,0,0);
    }
}
