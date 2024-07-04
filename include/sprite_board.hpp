#ifndef SPRITE_BOARD_HPP
#define SPRITE_BOARD_HPP

#include <SFML/Graphics.hpp>
#include "tetromino.hpp"

static constexpr int SPRITE_BOARD_HEIGHT = 24;
static constexpr int SPRITE_BOARD_WIDTH = 14;

class SpriteBoard {
    private:
        std::array<std::array<sf::Sprite*, BOARD_WIDTH>, BOARD_HEIGHT> sprite_board_matrix;
        sf::Sprite score_box;
        sf::Text score_text;
        sf::Sprite next_tetromino_box;

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
        void initializeSpriteMatrix(sf::Texture& sprite_texture);

        void initializeScoreBox(sf::Texture& score_box_texture, sf::Font& score_box_font);

        void initializeNextTetrominoBox(sf::Texture& score_box_texture);

        // returns the sprite at specific coordinates
        sf::Sprite getBoardSprite(int row, int col);

        // returns the score_box sprite
        sf::Sprite getScoreBoxSprite();

        // returns the score text
        sf::Text getScoreText();

        // returns next tetromino box sprite
        sf::Sprite getNextTetrominoBox();

        // changes score text
        void setScoreText(int score);

        // returns width of board
        int getWidth();

        // returns height of board
        int getHeight();

        void colorTetromino(Tetromino* tetromino);

        void reset();
};

#endif