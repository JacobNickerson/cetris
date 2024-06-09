#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include <array>

#include "block.hpp"

// Tetromino type
enum class TType { I, O, T, J, L, S, Z, };

class Tetromino {
    private:
        std::array<Block*, 4> blocks;
        std::array<int, 2> position;
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
        bool up();

        // Moves the tetromino down.
        // Returns true if success, false if not.
        bool down();

        // Moves the tetromino left.
        // Returns true if success, false if not.
        bool left();

        // Moves the tetromino right. 
        // Returns true if success, false if not.
        bool right();

        // Shoves the tetromino to the ghost position.
        // Returns true if success, false if not.
        bool hard_drop();

        // Calculates how far down the ghost position is.
        int ghost_position();
};

#endif
