#include "I_tetromino.hpp"
#include "tetromino.hpp"

const std::array<std::array<std::pair<int, int>, 4>, 4> rotation_positions = {{
        { {{0, -1}, {0, 0}, {0, 1}, {0, 2}} },
        { {{-1, 0}, {0, 0}, {1, 0}, {2, 0}} },
        { {{0, -2}, {0, -1}, {0, 0}, {0, 1}} },
        { {{-2, 0}, {-1, 0}, {0, 0}, {1, 0}} }
}};

