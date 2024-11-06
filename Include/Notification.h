//
// Created by Amaury Paillard on 06/11/2024.
//

#ifndef NOTIFIER_H
#define NOTIFIER_H

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Time.hpp"


class Notification {
public:
    Notification(const std::string& message, const sf::Font& font, const sf::Vector2f position)
        : duration(sf::seconds(3)), elapsedTime(sf::Time::Zero) {

        text.setFont(font);
        text.setString(message);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setPosition(position);

        background.setSize(sf::Vector2f(text.getLocalBounds().width + 20, text.getLocalBounds().height + 20));
        background.setFillColor(sf::Color(0, 0, 0, 180));
        background.setPosition(position.x - 10, position.y - 10);
    }

    void update(const sf::Time deltaTime) {
        elapsedTime += deltaTime;
        if (elapsedTime < sf::seconds(0.5f)) {
            const float progress = elapsedTime / sf::seconds(0.5f);
            const float yOffset = -50.0f * (1 - progress);
            text.move(0, yOffset);
            background.move(0, yOffset);
        }
    }

    bool isExpired() const {
        return elapsedTime >= duration;
    }

    void setPosition(const sf::Vector2f newPosition) {
        text.setPosition(newPosition);
        background.setPosition(newPosition.x - 10, newPosition.y - 10);
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(background);
        window.draw(text);
    }

private:
    sf::Text text;
    sf::RectangleShape background{};
    sf::Time duration;
    sf::Time elapsedTime;
};

#endif //NOTIFIER_H
