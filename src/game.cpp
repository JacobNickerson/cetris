#include "game.hpp"

void Game::run() {
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Cetris");

    // Initialize graphics
    if (!game_graphics_engine.initialize()) {
        std::cout << "Error loading sprites/font" << std::endl;
        return;
    }

    // Initializing audio
    if (!game_audio_engine.initialize()) {
        std::cout << "Error loading audio files" << std::endl;
        return;
    }

    while (window.isOpen()) {
        while (window.isOpen() && game_state == GameState::Title) {
            titleScreen(window);
        }

        while (window.isOpen() && game_state == GameState::GameRunning) {
            playGame(window);
        }

        while (window.isOpen() && game_state == GameState::GameOver) {
            endScreen(window);
            reset();
        }
    }
}

bool Game::spawnTetromino(Tetromino* tetromino) {
    tetromino->reset();
    tetromino->movePivot(2,6, game_board);
    if (!tetromino->constructTetromino(game_board)) return false;
    tetromino->activate();
    game_graphics_engine.colorTetromino(tetromino);
    return true;
}

bool Game::spawnTetromino(Tetromino* tetromino, int row, int col) {
    tetromino->movePivot(row, col, game_board);
    if (!tetromino->constructTetromino(game_board)) return false;
    tetromino->activate();
    game_graphics_engine.colorTetromino(tetromino);
    return true;
}

void Game::titleScreen(sf::RenderWindow& window) {
    sf::Clock render_clock;
    int time_elapsed;
    while (window.isOpen() && game_state == GameState::Title) {
        sf::Event event;
        time_elapsed = render_clock.getElapsedTime().asMilliseconds();
        // pollEvent pops any new events off the event stack and breaks when empty
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { 
                window.close(); 
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                game_audio_engine.playMenuTransition();
                // rendering the transition animation
                game_graphics_engine.titleToPlayAnimation(window);
                game_state = GameState::GameRunning;
                return;
            }
        }
        if (time_elapsed <= 1020) {
            game_graphics_engine.titleSlideAnimation(time_elapsed);
        }

        window.clear();
        window.draw(game_graphics_engine.menu_background);
        if (time_elapsed <= 2000) {
            window.draw(game_graphics_engine.title_text);
        } else if (time_elapsed % 1000 < 500) {
            window.draw(game_graphics_engine.title_text);
        }
        if (time_elapsed >= 2400) {
            window.draw(game_graphics_engine.press_to_start_text);
        }
        window.display();
    }
}

void Game::playGame(sf::RenderWindow& window) {
    // Playing transition
    game_graphics_engine.titleToPlayAnimation2(window, game_board, next_tet_board);

    // moving our tetromino to the correct spawn location and generating its blocks
    Tetromino* tetropointer = tetrominos[RNG_distribution(RNG)];
    Tetromino* next_tetropointer = tetrominos[RNG_distribution(RNG)];
    spawnTetromino(tetropointer);
    next_tet_board.activate(next_tetropointer);
    game_graphics_engine.colorNextTetromino(next_tetropointer);


    // resetting our clock to 0
    game_clock.restart();

    while (window.isOpen() && game_state == GameState::GameRunning) {
        if (game_clock.getElapsedTime().asMilliseconds() >= std::max(1000-(100*game_level), 50)) {  // tetromino moves down after a certain elapsed time
            game_clock.restart();
            if (!tetropointer->down(game_board)) {
                game_audio_engine.playPlace();
                placeTetromino(tetropointer, next_tetropointer);
                if (!spawnTetromino(tetropointer)) {
                    game_state = GameState::GameOver;
                    return;
                }
            }
            game_graphics_engine.colorTetromino(tetropointer);
        }
        // User Inputs
        sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) { 
                    window.close(); 
                } else if (event.type == sf::Event::KeyPressed) {
                    switch (event.key.code) {
                        case sf::Keyboard::S: 
                            // moveDown();
                            if (!tetropointer->down(game_board)) {
                                game_audio_engine.playPlace();
                                placeTetromino(tetropointer, next_tetropointer);
                                if (!spawnTetromino(tetropointer)) {
                                    game_state = GameState::GameOver;
                                    return;
                                }
                            }
                            game_graphics_engine.colorTetromino(tetropointer);
                            break;
                        case sf::Keyboard::A:
                            if(!tetropointer->left(game_board)) {
                                game_audio_engine.playCollision();
                            }
                            game_graphics_engine.colorTetromino(tetropointer);
                            break;
                        case sf::Keyboard::D:
                            if(!tetropointer->right(game_board)) {
                                game_audio_engine.playCollision();
                            }
                            game_graphics_engine.colorTetromino(tetropointer);
                            break;
                        case sf::Keyboard::Q:
                            if (!tetropointer->rotateLeft(game_board)) {
                                game_audio_engine.playCollision();
                            }
                            game_graphics_engine.colorTetromino(tetropointer);
                            break;
                        case sf::Keyboard::E:
                            if (!tetropointer->rotateRight(game_board)) {
                                game_audio_engine.playCollision();
                            }
                            game_graphics_engine.colorTetromino(tetropointer);
                            break;
                        case sf::Keyboard::Space:
                            game_audio_engine.playHardDrop();
                            tetropointer->hardDrop(game_board);
                            game_graphics_engine.colorTetromino(tetropointer);
                            placeTetromino(tetropointer, next_tetropointer);
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
        window.draw(game_graphics_engine.play_background);
        for (int i = 2; i < game_graphics_engine.getHeight()-1; i++) {
            for (int j = 1; j < game_graphics_engine.getWidth()-1; j++) {
                if (game_board.getBlock(i, j)->isActive()) {
                    window.draw(game_graphics_engine.getBoardSprite(i,j));
                }
            }
        }

        for (int i = 0; i < 4; i++) { // i got lazy and didn't make another getter
            for (int j = 0; j < 4; j++) {  // its a 4 length square box every time lol
                if (next_tet_board.getBlock(i, j)->isActive()) {
                    window.draw(game_graphics_engine.getNextSprite(i, j));
                }
            }
        }

        window.draw(game_graphics_engine.score_text);
        window.draw(game_graphics_engine.level_text);
        window.display();
    }
}

void Game::reset() {
    game_board.reset();
    game_graphics_engine.reset();
    next_tet_board.reset();
    game_state = GameState::Title;
    game_score = 0;
    game_level = 0;
}

void Game::endScreen(sf::RenderWindow& window) {
    sf::Clock render_clock;
    game_graphics_engine.setScoreText(game_score);
    while (window.isOpen() && game_state == GameState::GameOver) {
        sf::Event event;

        // pollEvent pops any new events off the event stack and breaks when empty
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { 
                window.close(); 
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                game_state = GameState::Title;
                sf::RectangleShape transition_rect(sf::Vector2f(1600,900));
                sf::Color transition_color(255,255,255,0);
                transition_rect.setFillColor(transition_color);
                for (int i = 0; i < 52; i++) {  // can't use color.a for comparison
                    window.clear();
                    window.draw(game_graphics_engine.menu_background);
                    if (render_clock.getElapsedTime().asMilliseconds() >= 1000) {
                        window.draw(game_graphics_engine.end_screen_text);
                    }

                    if (render_clock.getElapsedTime().asMilliseconds() >= 2000) {
                        window.draw(game_graphics_engine.end_score_text);
                    }

                    if (render_clock.getElapsedTime().asMilliseconds() >= 3000) {
                        window.draw(game_graphics_engine.end_prompt_text);
                    }
                    window.draw(transition_rect);
                    window.display();
                    transition_color.a += 5;
                    transition_rect.setFillColor(transition_color);
                }
                return;
            }
        }
        
        window.clear();
        window.draw(game_graphics_engine.menu_background);
        if (render_clock.getElapsedTime().asMilliseconds() >= 1000) {
            window.draw(game_graphics_engine.end_screen_text);
        }

        if (render_clock.getElapsedTime().asMilliseconds() >= 2000) {
            window.draw(game_graphics_engine.end_score_text);
        }

        if (render_clock.getElapsedTime().asMilliseconds() >= 3000) {
            window.draw(game_graphics_engine.end_prompt_text);
        }
        window.display();
    }
}

void Game::placeTetromino(Tetromino*& tetropointer, Tetromino*& next_tetropointer) {
    int clears = game_board.checkPlacement(tetropointer->getBlocks(), game_level, game_clears, game_score);
    switch (clears) {
        case 1:
            game_audio_engine.playOneLineClear();
            break;
        case 2:
            game_audio_engine.playTwoLineClear();
            break;
        case 3:
            game_audio_engine.playThreeLineClear();
            break;
        case 4:
            game_audio_engine.playFourLineClear();
            break;
    }
    game_graphics_engine.setScoreText(game_score);
    tetropointer = next_tetropointer;
    next_tet_board.reset();
    next_tetropointer = tetrominos[RNG_distribution(RNG)];
    next_tet_board.activate(next_tetropointer);
    game_graphics_engine.colorNextTetromino(next_tetropointer);
    game_graphics_engine.setLevelText(game_level);
}

// void Game::moveDown() {
//     if (!tetropointer->down(game_board)) {
//         game_audio_engine.playPlace();
//         placeTetromino(tetropointer, next_tetropointer, game_level, game_clears, distribution(RNG), score);
//         if (!spawnTetromino(tetropointer)) {
//             game_state = GameState::GameOver;
//             return;
//         }
//     }
//     game_graphics_engine.colorTetromino(tetropointer);
// }