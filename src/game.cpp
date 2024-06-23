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

    // Initializing our sprite texture
    sf::Texture block_texture;
    if (!block_texture.loadFromFile("images/block.png")) {
        std::cout << "TEXTURE FAILED TO LOAD" << std::endl;
        return;
    }

    // Initializing our sprite board
    SpriteBoard sprite_board;
    sprite_board.initialize(block_texture);
    game_sprite_board = sprite_board;

    // Initializing game logic board
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
                switch (event.key.code) {
                    case sf::Keyboard::S: 
                        if (!testromino.down(board)) {
                            game_board.checkPlacement(testromino.getBlocks());
                            if (!spawnTetromino(testromino)) {
                                game_board.reset();
                                game_state = GameState::Title;
                            }
                        }
                        game_sprite_board.colorTetromino(testromino);
                        break;
                    case sf::Keyboard::A:
                        testromino.left(board);
                        game_sprite_board.colorTetromino(testromino);
                        break;
                    case sf::Keyboard::D:
                        testromino.right(board);
                        game_sprite_board.colorTetromino(testromino);
                        break;
                    case sf::Keyboard::Q:
                        testromino.rotateLeft(board);
                        game_sprite_board.colorTetromino(testromino);
                        break;
                    case sf::Keyboard::E:
                        testromino.rotateRight(board);
                        game_sprite_board.colorTetromino(testromino);
                        break;
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !live_block) {
            spawnTetromino(testromino);
        }
        
        window.clear();
        for (int i = 2; i < game_sprite_board.getHeight(); i++) {
            for (int j = 0; j < game_sprite_board.getWidth(); j++) {
                if (game_board.getBlock(i, j)->isActive()) {
                    window.draw(*sprite_board.getSprite(i,j));
                }
            }
        }
        window.display();
    } 

    if (game_state == GameState::Title) {
        std::cout << "YES!!!" << std::endl;
    }
}

void Game::playGame() {
    game_state = GameState::GameRunning;
}

bool Game::spawnTetromino(Tetromino& tetromino) {
    tetromino.reset();
    tetromino.set(0, game_board.getBlock(2,6), sf::Color(0,255,255));
    if (!tetromino.constructTetromino(game_board)) return false;
    tetromino.activate();
    game_sprite_board.colorTetromino(tetromino);
    live_block = true;
    return true;
}

bool Game::spawnTetromino(Tetromino& tetromino, int row, int col) {
    tetromino.movePivot(row, col,game_board);
    if (!tetromino.constructTetromino(game_board)) return false;
    tetromino.activate();
    game_sprite_board.colorTetromino(tetromino);
    live_block = true;
    return true;
}