#include "graphics_engine.hpp"
#include <iostream>

void GraphicsEngine::initialize() {
    // Initialize sprites for the play field matrix
    block_texture.loadFromFile("images/block.png");
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            sprite_board_matrix[i][j]->setTexture(block_texture);
            sprite_board_matrix[i][j]->setScale(sf::Vector2f(0.5, 0.5));
            sprite_board_matrix[i][j]->setPosition(sf::Vector2f(200.0, 45.0));
            sprite_board_matrix[i][j]->move(sf::Vector2f(32.0*j, 32.0*i));
        }
    }

    box_texture.loadFromFile("images/scorebox.png");
    score_box.setTexture(box_texture);
    score_box.setScale(sf::Vector2f(0.5,0.5));
    score_box.setPosition(sf::Vector2f(744, 109.0));

    // Initialize font for all text in the game
    game_font.loadFromFile("fonts/tetris-font.ttf"); 

    // Initialize score text for score window
    score_text.setString("0");
    score_text.setFont(game_font);
    score_text.setFillColor(sf::Color::White);
    score_text.setCharacterSize(50);
    
    float score_textX = score_box.getPosition().x + ((score_box.getGlobalBounds().width - score_text.getGlobalBounds().width)/2);
    float score_textY = score_box.getPosition().y + ((score_box.getGlobalBounds().height - score_text.getGlobalBounds().height)/2);

    score_text.setPosition(sf::Vector2f(score_textX, score_textY));

    next_tetromino_box.setTexture(box_texture);
    next_tetromino_box.setScale(sf::Vector2f(0.5,0.5));
    next_tetromino_box.setPosition(sf::Vector2f(744, 301.0));

    // Initialize Sprites for next tetromino matrix
    for (int i = 0; i < next_tetromino_matrix.size(); i++) {
        for (int j = 0; j < next_tetromino_matrix[0].size(); j++) {
            next_tetromino_matrix[i][j]->setTexture(block_texture);
            next_tetromino_matrix[i][j]->setScale(sf::Vector2f(0.5, 0.5));
            next_tetromino_matrix[i][j]->setPosition(sf::Vector2(next_tetromino_box.getPosition().x+(32*3), next_tetromino_box.getPosition().y+(32*1))); // offset by block size * number of blocks, ie 32 px * 3 blocks
            next_tetromino_matrix[i][j]->move(sf::Vector2f(32.0*j, 32.0*i));
        }
    }

    // Initialize text for level window
    level_text.setFont(game_font);
    level_text.setPosition(sf::Vector2f(score_text.getPosition().x, score_text.getPosition().y+(12*32))); // position is set relative to score_text, call its init first
    level_text.setString("1");                                                                            // 12 * 32 corresponds to twelve 32 pixel squares down
    level_text.setFillColor(sf::Color::White);
    level_text.setCharacterSize(50);
}


sf::Sprite GraphicsEngine::getBoardSprite(int row, int col) {
    return *sprite_board_matrix[row][col];
}

sf::Sprite GraphicsEngine::getScoreBoxSprite() {
    return score_box;
}

sf::Text GraphicsEngine::getScoreText() {
    return score_text;
}

sf::Text GraphicsEngine::getLevelText() {
    return level_text;
}

void GraphicsEngine::setLevelText(int level) {
    level_text.setString(std::to_string(level+1));
}

sf::Sprite GraphicsEngine::getNextTetrominoBox() {
    return next_tetromino_box;
}

sf::Sprite GraphicsEngine::getNextSprite(int i, int j) {
    return *next_tetromino_matrix[i][j];
}

void GraphicsEngine::setScoreText(int score) {
    score_text.setString(std::to_string(score));
    float score_textX = score_box.getPosition().x + ((score_box.getGlobalBounds().width - score_text.getLocalBounds().width)/2);
    float score_textY = score_box.getPosition().y + ((score_box.getGlobalBounds().height - score_text.getLocalBounds().height)/2);

    score_text.setPosition(sf::Vector2f(score_textX, score_textY));
}

int GraphicsEngine::getWidth() {
    return sprite_board_matrix[0].size();
}

int GraphicsEngine::getHeight() {
    return sprite_board_matrix.size();
}

void GraphicsEngine::colorTetromino(Tetromino* tetromino) {
    for (Block* block : tetromino->getBlocks()) {
        sprite_board_matrix[block->getRow()][block->getColu()]->setColor(tetromino->getColor());
    }
}

void GraphicsEngine::reset() {
    setScoreText(0);
    setLevelText(0);
}

void GraphicsEngine::colorNextTetromino(Tetromino* tetromino) {
    std::array<std::pair<int, int>, 4> rotation_offsets = tetromino->getRotationPositions();
    for (int i = 0; i < 4; i++) {
        next_tetromino_matrix[2+rotation_offsets[i].first][1+rotation_offsets[i].second]->setColor(tetromino->getColor());
    }
}
