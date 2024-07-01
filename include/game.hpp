#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"
#include "sprite_board.hpp"
#include <vector>
#include "tetromino_types.hpp"

enum class GameState {
    Title,
    GameRunning,
    GameOver
};

class Game {
    private:
        Board game_board;
        SpriteBoard game_sprite_board;
        GameState game_state;
        sf::Font game_font;
        int score;
        std::vector<Tetromino*> tetrominos;

    public:
        Game() {
            game_state = GameState::Title;
            game_font.loadFromFile("./fonts/tetris-font.ttf");
            score = 0;
            tetrominos.push_back(new I_Tetromino);
            tetrominos.push_back(new J_Tetromino);
            tetrominos.push_back(new L_Tetromino);
            tetrominos.push_back(new O_Tetromino);
            tetrominos.push_back(new S_Tetromino);
            tetrominos.push_back(new T_Tetromino);
            tetrominos.push_back(new Z_Tetromino);
        }

        ~Game() {
            for (int i = 0; i < tetrominos.size(); i++) {
                delete tetrominos[i];
                tetrominos[i] = nullptr;
            }
        }

        void run();

        // places the tetromino in the current position and spawns a new one at ()
        bool spawnTetromino(Tetromino* tetromino);

        // places the tetromino in the current position and spawns one at a given coordinate
        bool spawnTetromino(Tetromino* tetromino, int row, int col);

        void titleScreen(sf::RenderWindow& window, sf::Text& title, sf::Text& press_to_start_message);
        
        void playGame(sf::RenderWindow& window, Tetromino* tetropointer);

        bool initializeSprites();

        void reset();

        void endScreen(sf::RenderWindow& window, sf::Text& end_text, sf::Text& end_score);
};

#endif