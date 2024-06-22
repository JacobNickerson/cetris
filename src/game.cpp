#include "game.hpp"
#include <array>
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

    // Initializing our test matrix
    sf::Texture block_texture;
    block_texture.loadFromFile("images/block.png");
    std::array<std::array<sf::Sprite, 12>, 23> board_sprites;
    for (int i = 0; i < board_sprites.size(); i++) {
        for (int j = 0; j < board_sprites[0].size(); j++) {
            board_sprites[i][j].setTexture(block_texture);
            board_sprites[i][j].setScale(sf::Vector2f(0.35, 0.35));
            board_sprites[i][j].move(sf::Vector2f(85*0.35*j,85*0.35*i));
        }
    }

    // Making das boardenheimer
    Board board;

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

    // Game is being played
    while (window.isOpen() && game_state == GameState::GameRunning) {
    sf::Event event;
        
       while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { 
                window.close(); 
            }
        }
        
        window.clear();
        for (int i = 0; i < board_sprites.size(); i++) {
            for (int j = 0; j < board_sprites[0].size(); j++) {
                if (board.getBlock(i, j)->isActive()) {
                    window.draw(board_sprites[i][j]);
                }
            }
        }
        window.display();
    } 
}

void Game::playGame() {
    game_state = GameState::GameRunning;
}