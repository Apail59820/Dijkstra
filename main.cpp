#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Dijkstra Algorithm");
    window.setFramerateLimit(60);
    sf::Event event = {sf::Event::KeyPressed, sf::Event::KeyReleased};

    while (window.isOpen()) {
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
    }
    return 0;
}
