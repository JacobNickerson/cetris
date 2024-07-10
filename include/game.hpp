#ifndef GAME_HPP
#define GAME_HPP

#include "audio_engine.hpp"
#include "block.hpp"
#include "board.hpp"
#include "graphics_engine.hpp"
#include "next_tetromino_board.hpp"
#include "tetromino_types.hpp"
#include <array>
#include <iostream>
#include <random>
#include <vector>


enum class GameState {
    Title,
    GameRunning,
    GameOver
};

class Game {
    public:
        Game() : game_state(GameState::Title), game_score(0), game_level(0), game_clears(0), RNG(rd()), RNG_distribution(0,6) {
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

        // takes the title text and press to start text as parameters and renders them on a title screen
        // waits for any keyboard input to change gamestates and return from method
        void titleScreen(sf::RenderWindow& window);
        
        // the main game loop
        void playGame(sf::RenderWindow& window);

        // calls all the reset methods for each of game's members
        void reset();

        // takes end text and end score text as parameters and renders them on endscreen
        // awaits inputting 'Esc' to transition gamestate back to titlescreen
        void endScreen(sf::RenderWindow& window);

        // various functions are called whenever a tetromino is placed
        // this method bundles them together to make the logic cleaner
        void placeTetromino(Tetromino*& tetropointer, Tetromino*& next_tetropointer);

        void moveDown();

        // STICKY GRAVITY!
        void lineClear();
    
    private:
        int game_score;
        int game_level; 
        int game_clears;
        AudioEngine game_audio_engine;
        Board game_board;
        NextTetBoard next_tet_board;
        GameState game_state;
        GraphicsEngine game_graphics_engine;
        sf::Clock game_clock;
        sf::Font game_font;
        std::vector<Tetromino*> tetrominos;
        std::random_device rd;
        std::mt19937 RNG;
        std::uniform_int_distribution<> RNG_distribution;  // setting up RNG to generate a number in range [0,6]
};

#endif