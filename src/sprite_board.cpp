#include "sprite_board.hpp"

void SpriteBoard::initialize(sf::Texture& sprite_texture) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            sprite_board_matrix[i][j]->setTexture(sprite_texture);
            sprite_board_matrix[i][j]->setScale(sf::Vector2f(0.5, 0.5));
            sprite_board_matrix[i][j]->move(sf::Vector2f(32.0*j, 32.0*i));
        }
    }
}

sf::Sprite* SpriteBoard::getSprite(int row, int col) {
    return sprite_board_matrix[row][col];
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