#ifndef SCOREBOX_HPP
#define SCOREBOX_HPP

#include <array>
#include <SFML/Graphics.hpp>

class ScoreBox {
    private:
        std::array<sf::Sprite*, 30> border;        

    public:
        ScoreBox() {
            for (size_t i = 0; i < border.size(); i++) {
                border[i] = new sf::Sprite;
            }
        }
        
        ~ScoreBox() {
            for (size_t i = 0; i < border.size(); i++) {
                delete border[i];
                border[i] = nullptr;
            }
        }

        void initializeSprites(sf::Texture& texture);

        sf::Sprite* getSprite(int i);
};

#endif