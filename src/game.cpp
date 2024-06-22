#include "game.hpp"
#include <iostream>

void Game::run() {
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Cetris");

    // Initializing title with our specified font
    sf::Text title;
    sf::Font font;
    font.loadFromFile("./fonts/tetris-font.ttf");
    title.setFont(font);
    title.setString("Cetris!");
    title.setCharacterSize(100);
    title.setFillColor(sf::Color::White);

    // center text
    sf::FloatRect textRect = title.getLocalBounds();
    title.setOrigin(textRect.left + textRect.width/2.0f,
                textRect.top  + textRect.height/2.0f);
    title.setPosition(sf::Vector2f(1600/2.0f,900/2.0f));

    sf::Text press_to_start_message = title;
    press_to_start_message.setString("Press any key to start");
    press_to_start_message.setCharacterSize(50);
    sf::FloatRect start_rect = press_to_start_message.getLocalBounds();
    press_to_start_message.setOrigin(start_rect.left + start_rect.width/2.0f,
                start_rect.top  + start_rect.height/2.0f);
    press_to_start_message.setPosition(sf::Vector2f(1600/2.0f,900/2.0f + 150.0f));

    // Initializing our fake tetromino
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

    // Render loop. Everything is rendered here.
    while (window.isOpen() && game_state == GameState::Title) {
        sf::Event event;

        // pollEvent pops any new events off the event stack and breaks when empty
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { 
                window.close(); 
            }
            if (event.type == sf::Event::KeyPressed) {
               playGame(); 
            }
        }
        

        window.clear();
        window.draw(title);
        window.draw(press_to_start_message);
        window.display();
    }

    while (window.isOpen() && game_state == GameState::GameRunning) {
    sf::Event event;
        
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
        window.draw(example_block_sprite);
        window.draw(example_block_sprite2);
        window.draw(example_block_sprite3);
        window.draw(example_block_sprite4);
        window.display();
    } 
}

void Game::playGame() {
    board = Board();
    game_state = GameState::GameRunning;
}