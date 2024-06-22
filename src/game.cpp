#include "game.hpp"
#include <iostream>

void Game::start() {
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Cetris");

    // Initializing a message with our specified font
    sf::Text message;
    sf::Font font;
    font.loadFromFile("./fonts/tetris-font.ttf");
    message.setFont(font);
    message.setString("Cetris!");
    message.setCharacterSize(100);
    message.setFillColor(sf::Color::White);

    // Create a sprite and texture it
    sf::Sprite example_block_sprite;
    sf::Texture block_texture;
    block_texture.loadFromFile("images/block.png");
    example_block_sprite.setTexture(block_texture);
    example_block_sprite.setColor(sf::Color(255, 0, 0));
    example_block_sprite.move(sf::Vector2f(0.f,150.f));
    sf::Sprite example_block_sprite2 = example_block_sprite;
    example_block_sprite2.move(sf::Vector2f(0.f,85.f));
    sf::Sprite example_block_sprite3 = example_block_sprite2;
    example_block_sprite3.move(sf::Vector2f(0.f,85.f));
    sf::Sprite example_block_sprite4 = example_block_sprite3;
    example_block_sprite4.move(sf::Vector2f(85.f,0.f));
    std::vector<sf::Sprite> blockey = {example_block_sprite, example_block_sprite2, example_block_sprite3, example_block_sprite4};

    // Render loop. Everything is rendered here.
    while (window.isOpen()) {
        sf::Event event;

        // pollEvent pops any new events off the event stack and breaks when empty
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { 
                window.close(); 
            }
            if (event.type == sf::Event::KeyPressed) {

            }
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            example_block_sprite.move(sf::Vector2f(1.f, 0.f));
            example_block_sprite2.move(sf::Vector2f(1.f, 0.f));
            example_block_sprite3.move(sf::Vector2f(1.f, 0.f));
            example_block_sprite4.move(sf::Vector2f(1.f, 0.f));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            example_block_sprite.move(sf::Vector2f(-1.f, 0.f));
            example_block_sprite2.move(sf::Vector2f(-1.f, 0.f));
            example_block_sprite3.move(sf::Vector2f(-1.f, 0.f));
            example_block_sprite4.move(sf::Vector2f(-1.f, 0.f));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            example_block_sprite.move(sf::Vector2f(0.f, 1.f));
            example_block_sprite2.move(sf::Vector2f(0.f, 1.f));
            example_block_sprite3.move(sf::Vector2f(0.f, 1.f));
            example_block_sprite4.move(sf::Vector2f(0.f, 1.f));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            example_block_sprite.move(sf::Vector2f(0.f, -1.f));
            example_block_sprite2.move(sf::Vector2f(0.f, -1.f));
            example_block_sprite3.move(sf::Vector2f(0.f, -1.f));
            example_block_sprite4.move(sf::Vector2f(0.f, -1.f));
        }

        window.clear();
        window.draw(message);
        window.draw(example_block_sprite);
        window.draw(example_block_sprite2);
        window.draw(example_block_sprite3);
        window.draw(example_block_sprite4);
        window.display();
    }
}
