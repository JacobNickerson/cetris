#include "game.hpp"

void Game::run() {
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Cetris");
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2i window_position((desktop.width - window_width) / 2, (desktop.height - window_height) / 2);    
    window.setPosition(window_position);
    window.setFramerateLimit(240);

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
            game_audio_engine.stopMusic();
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
    game_clock.restart();
    game_graphics_engine.titleSlideAnimation(window, game_clock);
    int time_elapsed;
    while (window.isOpen() && game_state == GameState::Title) {
        sf::Event event;
        time_elapsed = game_clock.getElapsedTime().asMilliseconds();
        // pollEvent pops any new events off the event stack and breaks when empty
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { 
                window.close(); 
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                game_audio_engine.playMenuTransition();
                // rendering the transition animation
                game_graphics_engine.titleToPlayAnimation(window, game_clock);
                game_state = GameState::GameRunning;
                return;
            }
        }

        window.clear();
        window.draw(game_graphics_engine.menu_background);
        window.draw(game_graphics_engine.title_text);
        if (time_elapsed >= 1020 && time_elapsed % 1000 < 500) {
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

    // Starting our music and setting it to loop
    game_audio_engine.playMusic();

    // resetting our clock to 0
    game_clock.restart();

    // Events
    sf::Event event;
    // Clear Event queue
    while (window.pollEvent(event)) {}

    while (window.isOpen() && game_state == GameState::GameRunning) {
        if (game_clock.getElapsedTime().asMilliseconds() >= std::max(1000-(100*game_level), 50)) {  // tetromino moves down after a certain elapsed time
            game_clock.restart();
            if (!tetropointer->down(game_board)) {
                game_audio_engine.playPlace();
                placeTetromino(tetropointer, next_tetropointer);
                if (!spawnTetromino(tetropointer)) {
                    game_audio_engine.stopMusic();
                    game_audio_engine.playLossSound();
                    game_graphics_engine.lossAnimation(window, game_board, next_tet_board);
                    game_state = GameState::GameOver;
                    return;
                }
            }
            game_graphics_engine.colorTetromino(tetropointer);
        }
        // User Inputs
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
                                    game_audio_engine.stopMusic();
                                    game_audio_engine.playLossSound();
                                    game_graphics_engine.lossAnimation(window, game_board, next_tet_board);
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
                                game_audio_engine.stopMusic();
                                game_audio_engine.playLossSound();
                                game_graphics_engine.lossAnimation(window, game_board, next_tet_board);
                                game_state = GameState::GameOver;
                                return;
                            }
                            break;
                        case sf::Keyboard::P:
                            game_board.setUpDebug();
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
    game_graphics_engine.setEndScoreText(game_score);
    bool sound1_played = false;
    bool sound2_played = false;
    bool sound3_played = false;
    while (window.isOpen() && game_state == GameState::GameOver) {
        sf::Event event;

        // pollEvent pops any new events off the event stack and breaks when empty
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { 
                window.close(); 
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                game_state = GameState::Title;
                game_audio_engine.playEndToStartTransition();
                game_graphics_engine.endToTitleAnimation(window, render_clock);
                return;
            }
        }
        
        window.clear();
        window.draw(game_graphics_engine.menu_background);
        if (render_clock.getElapsedTime().asMilliseconds() >= 1000) {
            if (!sound1_played) {
                game_audio_engine.playCollision();
                sound1_played = !sound1_played;
            }
            window.draw(game_graphics_engine.end_screen_text);
        }

        if (render_clock.getElapsedTime().asMilliseconds() >= 2000) {
            if (!sound2_played) {
                game_audio_engine.playCollision();
                sound2_played = !sound2_played;
            }
            window.draw(game_graphics_engine.end_score_text);
        }

        if (render_clock.getElapsedTime().asMilliseconds() >= 3000) {
            if (!sound3_played) {
                game_audio_engine.playFourLineClear();
                sound3_played = !sound3_played;
            }
            window.draw(game_graphics_engine.end_prompt_text);
        }
        window.display();
    }
}

void Game::placeTetromino(Tetromino*& tetropointer, Tetromino*& next_tetropointer) {
    std::pair<int, int> line_clear = game_board.checkPlacement(tetropointer->getBlocks(), game_level, game_clears, game_score);
    switch (line_clear.first) {
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
    // game_board.stickyGravity(line_clear.second);
    std::vector<std::vector<std::pair<Block*, sf::Color>>> chunks = game_board.findConnectedChunks(line_clear.second);
    int chunk_num = 0;
    for (auto chunk : chunks) {
        int gravity_dist = game_board.findGravityPosition(chunk);
        game_board.activateGravityChunk(chunk, gravity_dist);
        for (auto pair : chunk) {
            game_graphics_engine.colorBlock(game_board.getBlock(pair.first->getRow()+gravity_dist, pair.first->getColu()));
        }
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