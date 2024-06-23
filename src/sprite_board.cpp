#include "sprite_board.hpp"
#include <iostream>

void SpriteBoard::initializeSpriteMatrix(sf::Texture& sprite_texture) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            sprite_board_matrix[i][j]->setTexture(sprite_texture);
            sprite_board_matrix[i][j]->setScale(sf::Vector2f(0.5, 0.5));
            sprite_board_matrix[i][j]->setPosition(sf::Vector2f(200.0, 45.0));
            sprite_board_matrix[i][j]->move(sf::Vector2f(32.0*j, 32.0*i));
        }
    }
}

void SpriteBoard::initializeScoreBox(sf::Texture& score_box_texture, sf::Font& score_box_font) {
    score_box.setTexture(score_box_texture);
    score_box.setScale(sf::Vector2f(0.5,0.5));
    score_box.setPosition(sf::Vector2f(744, 109.0));
    
    score_text.setString("1000");
    score_text.setFont(score_box_font);
    score_text.setFillColor(sf::Color::White);
    score_text.setCharacterSize(50);
    
    float score_textX = score_box.getPosition().x + ((score_box.getLocalBounds().width - score_text.getLocalBounds().width)/2);
    float score_textY = score_box.getPosition().y + ((score_box.getLocalBounds().height - score_text.getLocalBounds().height)/2);

    score_text.setPosition(sf::Vector2f(score_textX, score_textY));
    // score_text.setPosition(sf::Vector2f(score_box.getPosition().x, score_box.getPosition().y));
    // score_text.move(sf::Vector2f(score_box.get)
}

sf::Sprite SpriteBoard::getBoardSprite(int row, int col) {
    return *sprite_board_matrix[row][col];
}

sf::Sprite SpriteBoard::getScoreBoxSprite() {
    return score_box;
}

sf::Text SpriteBoard::getScoreText() {
    return score_text;
}

void SpriteBoard::setScoreText(int score) {
    score_text.setString(std::to_string(score));
}

int SpriteBoard::getWidth() {
    return sprite_board_matrix[0].size();
}

int SpriteBoard::getHeight() {
    return sprite_board_matrix.size();
}

void SpriteBoard::colorTetromino(Tetromino& tetromino) {
    for (Block* block : tetromino.getBlocks()) {
        sprite_board_matrix[block->getRow()][block->getCol()]->setColor(tetromino.getColor());
    }
}
