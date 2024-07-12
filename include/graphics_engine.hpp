#ifndef GRAPHICS_ENGINE_HPP
#define GRAPHICS_ENGINE_HPP

#include <SFML/Graphics.hpp>
#include "tetromino.hpp"

static constexpr int SPRITE_BOARD_HEIGHT = 24;
static constexpr int SPRITE_BOARD_WIDTH = 14;

class GraphicsEngine {
    public:
        sf::Sprite play_background;
        sf::Sprite menu_background;
        sf::Sprite next_tetromino_box;
        sf::Sprite score_box;
        sf::Text level_text;
        sf::Text score_text;
        sf::Text title_text;
        sf::Text press_to_start_text;
        sf::Text end_screen_text;
        sf::Text end_score_text;
        sf::Text end_prompt_text;
        
        // Constructor
        GraphicsEngine() : window_width(1600), window_height(900) {
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
        
        // the one ring.
        bool initialize();

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

        // slowly increases alpha of title text from 0 to 255 and translates text down
        void titleSlideAnimation(sf::RenderWindow& window, sf::Clock& render_clock);

        // plays an animation of a growing/shrinking black circle to transition from title to play
        void titleToPlayAnimation(sf::RenderWindow& window, sf::Clock& render_clock);
        void titleToPlayAnimation2(sf::RenderWindow& window, Board& game_board, Board& next_text_board);

        // plays an animation of a fade to white for the entire screen to transition from end to title
        void endToTitleAnimation(sf::RenderWindow& window, sf::Clock& render_clock);

        void setEndScoreText(int& game_score);

        void lossAnimation(sf::RenderWindow& window, Board& game_board, Board& next_tet_board);

        void colorBlock(Block*);
    
    private:
        int window_width;
        int window_height;
        std::array<std::array<sf::Sprite*, BOARD_WIDTH>, BOARD_HEIGHT> sprite_board_matrix;
        std::array<std::array<sf::Sprite*, 4>, 4> next_tetromino_matrix;
        sf::Texture block_texture;
        sf::Texture box_texture;
        sf::Texture menu_background_texture;
        sf::Texture play_background_texture;
        sf::Color title_color;
        sf::Font game_font;
};

#endif