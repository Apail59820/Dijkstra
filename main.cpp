#include <iostream>
#include <SFML/Graphics.hpp>

#include "Include/Point.h"

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Dijkstra Algorithm");
    window.setFramerateLimit(60);
    sf::Event event = {sf::Event::KeyPressed, sf::Event::KeyReleased};

    Point pointA("A");
    pointA.setPosition(sf::Vector2f(100, 100));

    Point pointB("B");
    pointB.setPosition(sf::Vector2f(200, 200));

    Point pointC("C");
    pointC.setPosition(sf::Vector2f(300, 300));

    std::vector<Point> points;
    points.push_back(pointA);
    points.push_back(pointB);
    points.push_back(pointC);

    sf::Vector2f mousePos;

    Point *currentDraggedPoint = nullptr;

    while (window.isOpen()) {
        mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    for (Point &point: points) {
                        if (point.getShape()->getGlobalBounds().contains(mousePos)) {
                            point.StartDragging(mousePos);
                            currentDraggedPoint = &point;
                        }
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left && currentDraggedPoint != nullptr) {
                    currentDraggedPoint->StopDragging();
                }
            }
        }

        for (Point &point: points) {
            point.Update(mousePos);
        }

        window.clear(sf::Color::White);

        for (const Point &point: points) {
            window.draw(point);
        }

        window.display();
    }
    return 0;
}
