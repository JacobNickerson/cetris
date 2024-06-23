#include "game.hpp"
#include <array>
#include "block.hpp"
#include "tetromino.hpp"
#include "L_tetromino.hpp"
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

    // Initializing our sprite matrix
    sf::Texture block_texture;
    block_texture.loadFromFile("images/block.png");
    std::array<std::array<sf::Sprite, 14>, 24> board_sprites;
    for (int i = 0; i < board_sprites.size(); i++) {
        for (int j = 0; j < board_sprites[0].size(); j++) {
            board_sprites[i][j].setTexture(block_texture);
            board_sprites[i][j].setScale(sf::Vector2f(0.5, 0.5));
            board_sprites[i][j].move(sf::Vector2f(32*j,32*i));
        }
    }

    // Making das boardenheimer
    Board board;
    game_board = board;

    // Making a controllable tetromino
    Tetromino testromino(sf::Color(255, 0, 255));

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
            } else if (event.type == sf::Event::KeyPressed && live_block) {
                if (event.key.code == sf::Keyboard::S) {
                    if (!testromino.down(board)) {
                        std::cout << "GAMING" << std::endl;
                    }
                    for (Block* block : testromino.getBlocks()) {
                        board_sprites[block->getRow()][block->getCol()].setColor(testromino.getColor());
                    }
                } else if (event.key.code == sf::Keyboard::W) {
                    testromino.up(board);
                    for (Block* block : testromino.getBlocks()) {
                        board_sprites[block->getRow()][block->getCol()].setColor(testromino.getColor());
                    }
                } else if (event.key.code == sf::Keyboard::A) {
                    testromino.left(board);
                    for (Block* block : testromino.getBlocks()) {
                        board_sprites[block->getRow()][block->getCol()].setColor(testromino.getColor());
                    }
                } else if (event.key.code == sf::Keyboard::D) {
                    testromino.right(board);
                    for (Block* block : testromino.getBlocks()) {
                        board_sprites[block->getRow()][block->getCol()].setColor(testromino.getColor());
                    }
                } else if (event.key.code == sf::Keyboard::Q) {
                    testromino.rotateLeft(board);
                    for (Block* block : testromino.getBlocks()) {
                        board_sprites[block->getRow()][block->getCol()].setColor(testromino.getColor());
                    }
                } else if (event.key.code == sf::Keyboard::E) {
                    testromino.rotateRight(board);
                    for (Block* block : testromino.getBlocks()) {
                        board_sprites[block->getRow()][block->getCol()].setColor(testromino.getColor());
                    }
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !live_block) {
            testromino.movePivot(2,5,game_board);
            testromino.expandPivot(game_board);
            testromino.activate();
            for (Block* block : testromino.getBlocks()) {
                board_sprites[block->getRow()][block->getCol()].setColor(testromino.getColor());
            }
            live_block = true;
        }
        
        window.clear();
        for (int i = 0; i < board_sprites.size(); i++) {
            for (int j = 0; j < board_sprites[0].size(); j++) {
                if (game_board.getBlock(i, j)->isActive()) {
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