#include "block.hpp"
#include "game.hpp"
#include "tetromino_types.hpp"
#include <array>
#include <iostream>

void Game::run() {
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Cetris");

    // Initializing our sprite texture
    sf::Texture block_texture;
    if (!block_texture.loadFromFile("images/block.png")) {
        std::cout << "BLOCK TEXTURE FAILED TO LOAD" << std::endl;
        return;
    }
    
    // Initializing our score box texture
    sf::Texture score_box_texture;
    if (!score_box_texture.loadFromFile("images/scorebox.png")) {
        std::cout << "SCOREBOX TEXTURE FAILED TO LOAD" << std::endl;
        return;
    }    

    // Initializing the game's font
    sf::Font game_font;
    if (!game_font.loadFromFile("fonts/tetris-font.ttf")) {
        std::cout << "FONT FAILED TO LOAD" << std::endl;
        return;
    }

    // Initializing our sprite board
    game_sprite_board.initializeSpriteMatrix(block_texture);

    // Initializing our scoreboard
    game_sprite_board.initializeScoreBox(score_box_texture, game_font);

    while (window.isOpen()) {
        while (window.isOpen() && game_state == GameState::Title) {
            titleScreen(window);
        }

        while (window.isOpen() && game_state == GameState::GameRunning) {
            std::cout << "play" << std::endl;
            playGame(window);
        }

        while (window.isOpen() && game_state == GameState::GameOver) {
            // wip
            std::cout << "GAME OVER MAN" << std::endl;
            reset();
        }
    }
}

bool Game::spawnTetromino(Tetromino* tetromino) {
    tetromino->reset();
    tetromino->movePivot(2,6, game_board);
    if (!tetromino->constructTetromino(game_board)) return false;
    tetromino->activate();
    game_sprite_board.colorTetromino(tetromino);
    return true;
}

bool Game::spawnTetromino(Tetromino* tetromino, int row, int col) {
    tetromino->movePivot(row, col, game_board);
    if (!tetromino->constructTetromino(game_board)) return false;
    tetromino->activate();
    game_sprite_board.colorTetromino(tetromino);
    return true;
}

void Game::titleScreen(sf::RenderWindow& window) {
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

    while (window.isOpen() && game_state == GameState::Title) {
        sf::Event event;

        // pollEvent pops any new events off the event stack and breaks when empty
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { 
                window.close(); 
            }
            if (event.type == sf::Event::KeyPressed) {
                game_state = GameState::GameRunning;
            }
        }
        
        window.clear();
        window.draw(title);
        window.draw(press_to_start_message);
        window.display();
    }
}

void Game::playGame(sf::RenderWindow& window) {
    // spawning a tetromino
    I_Tetromino example_tetromino;
    I_Tetromino* tetropointer = &example_tetromino; 
    spawnTetromino(tetropointer);


        while (window.isOpen() && game_state == GameState::GameRunning) {
            // User Inputs
            sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) { 
                        window.close(); 
                    } else if (event.type == sf::Event::KeyPressed) {
                        switch (event.key.code) {
                            case sf::Keyboard::S: 
                                if (!tetropointer->down(game_board)) {
                                    game_board.checkPlacement(tetropointer->getBlocks());
                                    if (!spawnTetromino(tetropointer)) {
                                        game_state = GameState::GameOver;
                                        return;
                                    }
                                    break;
                                }
                                game_sprite_board.colorTetromino(tetropointer);
                                break;
                            case sf::Keyboard::A:
                                tetropointer->left(game_board);
                                game_sprite_board.colorTetromino(tetropointer);
                                break;
                            case sf::Keyboard::D:
                                tetropointer->right(game_board);
                                game_sprite_board.colorTetromino(tetropointer);
                                break;
                            case sf::Keyboard::Q:
                                tetropointer->rotateLeft(game_board);
                                game_sprite_board.colorTetromino(tetropointer);
                                break;
                            case sf::Keyboard::E:
                                tetropointer->rotateRight(game_board);
                                game_sprite_board.colorTetromino(tetropointer);
                                break;
                        }
                    }
                }

            // rendering
            window.clear();
            for (int i = 2; i < game_sprite_board.getHeight()-1; i++) {
                for (int j = 1; j < game_sprite_board.getWidth()-1; j++) {
                    if (game_board.getBlock(i, j)->isActive()) {
                        window.draw(game_sprite_board.getBoardSprite(i,j));
                    }
                }
            }
            window.draw(game_sprite_board.getScoreBoxSprite());
            window.draw(game_sprite_board.getScoreText());
            window.display();
    }
}

void Game::reset() {
    game_board.reset();
    game_state = GameState::Title;
    score = 0;
}