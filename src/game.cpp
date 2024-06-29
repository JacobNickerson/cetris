#include "block.hpp"
#include "game.hpp"
#include "tetromino_types.hpp"
#include <array>
#include <iostream>

void Game::run() {
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Cetris");

    // Initializing title with our specified font
    sf::Text title;
    title.setFont(game_font);
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

    // Initializing endscreen with our specified font
    sf::Text end_text;
    end_text.setFont(game_font);
    end_text.setString("Game Over!");
    end_text.setCharacterSize(100);
    end_text.setFillColor(sf::Color::White);

    // center text
    sf::FloatRect end_text_rect = end_text.getLocalBounds();
    end_text.setOrigin(end_text_rect.left + end_text_rect.width/2.0f,
                end_text_rect.top  + end_text_rect.height/2.0f);
    end_text.setPosition(sf::Vector2f(1600/2.0f,900/2.0f));

    sf::Text end_score = end_text;
    end_score.setString("You Scored: 0 Points");
    end_score.setCharacterSize(50);
    sf::FloatRect end_rect = end_score.getLocalBounds();
    end_score.setOrigin(end_rect.left + end_rect.width/2.0f,
                end_rect.top  + end_rect.height/2.0f);
    end_score.setPosition(sf::Vector2f(1600/2.0f,900/2.0f + 150.0f));

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

    // Initializing our sprite board
    game_sprite_board.initializeSpriteMatrix(block_texture);

    // Initializing our scoreboard
    game_sprite_board.initializeScoreBox(score_box_texture, game_font);

    // spawning a tetromino
    Tetromino example_tetromino = I_Tetromino();
    Tetromino* tetropointer = &example_tetromino; 

    while (window.isOpen()) {
        while (window.isOpen() && game_state == GameState::Title) {
            titleScreen(window, title, press_to_start_message);
        }

        while (window.isOpen() && game_state == GameState::GameRunning) {
            playGame(window, tetropointer);
        }

        while (window.isOpen() && game_state == GameState::GameOver) {
            std::cout << "GAME OVER MAN" << std::endl;
            endScreen(window, end_text, end_score);
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

void Game::titleScreen(sf::RenderWindow& window, sf::Text& title, sf::Text& press_to_start_message) {
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

void Game::playGame(sf::RenderWindow& window, Tetromino* tetropointer) {
    // moving our tetromino to the correct spawn location and generating its blocks
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
                                score += game_board.checkPlacement(tetropointer->getBlocks());
                                game_sprite_board.setScoreText(score);
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
                        case sf::Keyboard::Space:
                            tetropointer->hardDrop(game_board);
                            game_sprite_board.colorTetromino(tetropointer);
                            score += game_board.checkPlacement(tetropointer->getBlocks());
                            game_sprite_board.setScoreText(score);
                            if (!spawnTetromino(tetropointer)) {
                                game_state = GameState::GameOver;
                                return;
                            }
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
    game_sprite_board.reset();
    game_state = GameState::Title;
    score = 0;
}

void Game::endScreen(sf::RenderWindow& window, sf::Text& end_text, sf::Text& end_score) {
    end_score.setString("You Scored: " + std::to_string(score));
    while (window.isOpen() && game_state == GameState::GameOver) {
        sf::Event event;

        // pollEvent pops any new events off the event stack and breaks when empty
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { 
                window.close(); 
            }
            if (event.type == sf::Event::KeyPressed) {
                game_state = GameState::Title;
            }
        }
        
        window.clear();
        window.draw(end_text);
        window.draw(end_score);
        window.display();
    }
}