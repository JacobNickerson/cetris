#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <optional>

#include <SFML/Graphics.hpp>

// Represents a block in the grid.
class Block {
    public:
        // Constructor
        Block(int x, int y) : colu(x), row(y) {};

        // "Activates" the block
        void activate();
        void activate(sf::Color);

        // Deactivates the block and removes its color.
        void deactivate();

        // returns x coord
        int getRow();

        // returns y coord
        int getColu();

        // returns exactly what you'd think
        bool isActive();

        // returns exactly what you'd think
        sf::Color getColo();
    
    private:
        const int colu; 
        const int row;
        std::optional<sf::Color> colo;
};

#endif