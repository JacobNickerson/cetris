#ifndef GRAPHICS_ENGINE_HPP
#define GRAPHICS_ENGINE_HPP

#include <SFML/Graphics.hpp>
#include "tetromino.hpp"

static constexpr int SPRITE_BOARD_HEIGHT = 24;
static constexpr int SPRITE_BOARD_WIDTH = 14;

class GraphicsEngine {
    private:
        std::array<std::array<sf::Sprite*, BOARD_WIDTH>, BOARD_HEIGHT> sprite_board_matrix;
        std::array<std::array<sf::Sprite*, 4>, 4> next_tetromino_matrix;
        sf::Sprite score_box;
        sf::Text score_text;
        sf::Sprite next_tetromino_box;
        sf::Text level_text;

    public:
        // Constructor
        GraphicsEngine() {
            for (size_t i = 0; i < BOARD_HEIGHT; i++) {
                for (size_t j = 0; j < BOARD_WIDTH; j++) {
                    sprite_board_matrix[i][j] = new sf::Sprite;
                }
            }
            for (size_t i = 0; i < next_tetromino_matrix.size(); i++) {
                for (size_t j = 0; j < next_tetromino_matrix[0].size(); j++) {
                    next_tetromino_matrix[i][j] = new sf::Sprite;
                }
            }
        }

        ~GraphicsEngine() {
            for (int i = 0; i < BOARD_HEIGHT; i++) {
                for (int j = 0; j < BOARD_WIDTH; j++) {
                    delete sprite_board_matrix[i][j];
                    sprite_board_matrix[i][j] = nullptr;
                }
            }
            for (size_t i = 0; i < next_tetromino_matrix.size(); i++) {
                for (size_t j = 0; j < next_tetromino_matrix[0].size(); j++) {
                    delete next_tetromino_matrix[i][j];
                    next_tetromino_matrix[i][j] = nullptr;
                }
            }
        }
        
        // Initialize sprites with an sf::Texture
        void initializeSpriteMatrix(sf::Texture& sprite_texture);

        void initializeScoreBox(sf::Texture& score_box_texture, sf::Font& score_box_font);

        void initializeNextTetrominoBox(sf::Texture& score_box_texture);

        void initializeNextTetrominoMatrix(sf::Texture& sprite_texture);

        void initializeLevelText(sf::Font& level_font);

        // returns the sprite at specific coordinates
        sf::Sprite getBoardSprite(int row, int col);

        // returns the score_box sprite
        sf::Sprite getScoreBoxSprite();

        // returns the score text
        sf::Text getScoreText();

        // returns the level text
        sf::Text getLevelText();

        // sets the level text
        void setLevelText(int level);

        // returns next tetromino box sprite
        sf::Sprite getNextTetrominoBox();

        // returns sprite from next tetromino matrix
        sf::Sprite getNextSprite(int i, int j);

        // changes score text
        void setScoreText(int score);

        // returns width of board
        int getWidth();

        // returns height of board
        int getHeight();

        void colorTetromino(Tetromino* tetromino);

        void reset();

        void colorNextTetromino(Tetromino* tetromino);
};

#endif