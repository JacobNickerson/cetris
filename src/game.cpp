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
    // Clear the event queue
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) { 
            window.close(); 
        }
    }

    while (window.isOpen() && game_state == GameState::Title) {
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

    // we need this for recursive gravity :shrug:
    std::vector<Block*> blocks;

    // Events
    sf::Event event;
    // Clear Event queue
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) { 
            window.close(); 
        }
    }

    while (window.isOpen() && game_state == GameState::GameRunning) {
        if (game_clock.getElapsedTime().asMilliseconds() >= std::max(1000-(100*game_level), 50)) {  // tetromino moves down after a certain elapsed time
            game_clock.restart();
            if (!tetropointer->down(game_board)) {
                game_audio_engine.playPlace();
                if (!tetrominoPlaced(tetropointer, next_tetropointer, window)) return;
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
                                if (!tetrominoPlaced(tetropointer, next_tetropointer, window)) return;
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
                            if (!tetrominoPlaced(tetropointer, next_tetropointer, window)) return;
                            break;
                        case sf::Keyboard::Escape:
                            game_state = GameState::Paused;
                            game_audio_engine.pauseMusic();
                            while (game_state == GameState::Paused) {
                                while (window.pollEvent(event)) {
                                    if (event.type == sf::Event::Closed) {
                                        window.close();
                                        return;
                                    }
                                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                                        game_state = GameState::GameRunning;
                                        game_audio_engine.playMusic();
                                    }
                                    
                                }
                                drawPlayScreen(window);
                                window.draw(game_graphics_engine.pause_text);
                                window.draw(game_graphics_engine.pause_prompt_text);
                                window.display();
                            } 
                    }
                }
            }
        drawPlayScreen(window);
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
    
    // Clear the event queue
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) { 
            window.close(); 
        }
    }

    while (window.isOpen() && game_state == GameState::GameOver) {

        // pollEvent pops any new events off the event stack and breaks when empty
        while (window.pollEvent(event)) {
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

void Game::placeTetrominoNew(std::vector<Block*> blocks, sf::RenderWindow& window) {
    // check for line clears
    std::vector<int> rows_to_clear;
    std::pair<int, int> line_clear = checkPlacement(blocks, rows_to_clear);
    if (line_clear.first >= 5) {
        game_audio_engine.playFourLineClear();
    } else {
        switch (line_clear.first) {
            case 0:
                return;
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
    }
    game_graphics_engine.lineClearAnimation(window, game_board, next_tet_board, rows_to_clear);
    for (int row : rows_to_clear) {
        game_board.removeRow(row);
    }
    // gravity
    std::vector<Block*> recursive_blocks;
    std::vector<std::vector<std::pair<Block*, sf::Color>>> chunks = game_board.findConnectedChunks(line_clear.second);
    for (auto chunk : chunks) {
        int gravity_dist = game_board.findGravityPosition(chunk);
        game_board.activateGravityChunk(chunk, gravity_dist);
        for (auto pair : chunk) {
            Block* block = game_board.getBlock(pair.first->getRow()+gravity_dist, pair.first->getColu());
            recursive_blocks.push_back(block);
            game_graphics_engine.colorBlock(block);
        }
    }
    placeTetrominoNew(recursive_blocks, window);
}

void Game::updateBoardAfterPlace(Tetromino*& tetropointer, Tetromino*& next_tetropointer) {
    // other stuff
    game_graphics_engine.setScoreText(game_score);
    tetropointer = next_tetropointer;
    next_tet_board.reset();
    next_tetropointer = tetrominos[RNG_distribution(RNG)];
    next_tet_board.activate(next_tetropointer);
    game_graphics_engine.colorNextTetromino(next_tetropointer);
    game_graphics_engine.setLevelText(game_level);
}

std::pair<int, int> Game::checkPlacement(std::vector<Block*> blocks, std::vector<int>& rows_to_clear) {
    std::vector<int> rows;
    int bottom_row = -1;
    int rows_cleared = 0;
    for (Block* block : blocks) {
        if (std::find(rows.begin(), rows.end(), block->getRow()) == rows.end()) {
            rows.push_back(block->getRow());
        }
    }
    for (int row : rows) {
        if (game_board.rowIsFull(row)) {
            rows_cleared++;
            rows_to_clear.push_back(row);
            bottom_row = std::max(row, bottom_row);
        }
    }
    int score_increase;
    int clears;
    if (rows_cleared >= 5) {
        score_increase = (300*rows_cleared)*(1+game_level);
    } else {
        switch (rows_cleared) {
            case 0:
                score_increase = 0;
                clears = 0;
                break;
            case 1:
                score_increase = 40*(1+game_level);
                clears = 1;
                break;
            case 2:
                score_increase = 100*(1+game_level);
                clears = 2;
                break;
            case 3:
                score_increase = 300*(1+game_level);
                clears = 3;
                break;
            case 4:
                score_increase = 1200*(1+game_level);
                clears = 4;
                break;
        }
    }
    game_clears += clears;
    if (game_clears >= 10) {
        game_clears %= 10;
        game_level++;
    }
    game_score += score_increase;
    return {clears, bottom_row};
}

bool Game::tetrominoPlaced(Tetromino*& tetropointer, Tetromino*& next_tetropointer, sf::RenderWindow& window) {
    std::vector<Block*> blocks;
    game_audio_engine.playPlace();
    for (Block* block : tetropointer->getBlocks()) {
        blocks.push_back(block);
    }
    placeTetrominoNew(blocks, window);
    updateBoardAfterPlace(tetropointer, next_tetropointer);
    blocks.clear();
    if (!spawnTetromino(tetropointer)) {
        game_audio_engine.stopMusic();
        game_audio_engine.playLossSound();
        game_graphics_engine.lossAnimation(window, game_board, next_tet_board);
        game_state = GameState::GameOver;
        return false;
    }
    return true;
}

void Game::drawPlayScreen(sf::RenderWindow& window) {
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
}