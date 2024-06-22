#include "game.hpp"

void Game::start() {
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Cetris");

    // Initializing a message with our specified font
    sf::Text message;
    sf::Font font;
    font.loadFromFile("./fonts/tetris-font.ttf");
    message.setFont(font);
    message.setString("Cetris!");
    message.setCharacterSize(100);
    message.setFillColor(sf::Color::White);

    // 
    
    // Render loop. Everything is rendered here.
    while (window.isOpen()) {
        sf::Event event;

        // pollEvent pops any new events off the event stack and breaks when empty
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { 
                window.close(); 
            }
        }

        window.clear();
        window.draw(message);
        window.display();
    }
}
