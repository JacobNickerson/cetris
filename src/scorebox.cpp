#include "scorebox.hpp"


void ScoreBox::initializeSprites(sf::Texture& texture) {
    for (size_t i = 0; i < border.size(); i++) {
        border[i]->setTexture(texture);
        border[i]->setScale(sf::Vector2f(0.5,0.5));
        border[i]->setOrigin(sf::Vector2f(-1600.0, -220.0));
    }
    for (size_t i = 0; i < 10; i++) {
        border[i]->move(sf::Vector2f(32*i, 0));
    }
    for (size_t i = 10; i < 15; i++) {
        border[i]->move(sf::Vector2f(0,32*(i-9)));
    }
    for(size_t i = 15; i < 20; i++) {
        border[i]->move(sf::Vector2f(32*9,32*(i-14)));
    }
    for (size_t i = 20; i < 30; i++) {
        border[i]->move(sf::Vector2f(32*(i-20), 32*5));
    }
}

sf::Sprite* ScoreBox::getSprite(int i) {
    return border[i];
}