#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include <array>
#include <utility>

#include "block.hpp"
#include "board.hpp"

// Tetromino type
enum class TType { I, O, T, J, L, S, Z, };

class Tetromino {
    private:
        std::array<Block*, 4> blocks;
        Block* pivot;
        TType type;

    public:
        // Initialization of a tetromino.
        Tetromino(TType type);

        // Returns the type of the tetromino.
        TType get_type();

        // Attempts to rotate the tetromino 90 degrees to the right.
        // Returns true if success, false if not.
        bool rotate_right();

        // Attempts to rotate the tetromino 90 degrees to the left.
        // Returns true if success, false if not.
        bool rotate_left();

        // Moves the tetromino up.  (Would this really get used?)
        // Returns true if success, false if not.
        bool up(Board& board);

        // Moves the tetromino down.
        // Returns true if success, false if not.
        bool down(Board& board);

        // Moves the tetromino left.
        // Returns true if success, false if not.
        bool left(Board& board);

        // Moves the tetromino right. 
        // Returns true if success, false if not.
        bool right(Board& board);

        // Shoves the tetromino to the ghost position.
        // Returns true if success, false if not.
        bool hard_drop();

        // Calculates how far down the ghost position is.
        int ghost_position();

        // Moves the pivot point
        void movePivot(int i, int j);

        // Generates the tetrominos current orientation on the board according to its
        // orientation and pivot point location
        void expandPivot();


};

#endif
