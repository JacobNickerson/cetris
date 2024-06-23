#ifndef SPRITE_BOARD_HPP
#define SPRITE_BOARD_HPP

#include <SFML/Graphics.hpp>
#include "tetromino.hpp"

static constexpr int SPRITE_BOARD_HEIGHT = 24;
static constexpr int SPRITE_BOARD_WIDTH = 14;

class SpriteBoard {
    private:
        std::array<std::array<sf::Sprite*, BOARD_WIDTH>, BOARD_HEIGHT> sprite_board_matrix;

    public:
        // Constructor
        SpriteBoard() {
            for (int i = 0; i < BOARD_HEIGHT; i++) {
                for (int j = 0; j < BOARD_WIDTH; j++) {
                    sprite_board_matrix[i][j] = new sf::Sprite;
                }
            }
        }

        ~SpriteBoard() {
            for (int i = 0; i < BOARD_HEIGHT; i++) {
                for (int j = 0; j < BOARD_WIDTH; j++) {
                    delete sprite_board_matrix[i][j];
                    sprite_board_matrix[i][j] = nullptr;
                }
            }
        }
        
        // Initialize sprites with an sf::Texture
        void initialize(sf::Texture& sprite_texture);

        // returns a pointer to the sprite at a specific coordinate
        sf::Sprite* getSprite(int row, int col);

        // returns width of board
        int getWidth();

        // returns height of board
        int getHeight();

        void colorTetromino(Tetromino& tetromino);
};

#endif