#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

    // Initialize circle shape, set it to be red.
    sf::CircleShape circle(100.0f);
    circle.setFillColor(sf::Color::Red);

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
        window.draw(circle);
        window.display();
    }

    return 0;
}
