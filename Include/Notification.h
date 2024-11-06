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
    Notification(const std::string& message, const sf::Font& font, sf::Vector2f position);

    void update(const sf::Time& dt);

    bool isExpired() const;

    void setPosition(sf::Vector2f newPosition);

    void draw(sf::RenderWindow &window) const;

private:
    sf::Text text;
    sf::RectangleShape background{};
    sf::Time duration;
    sf::Time elapsedTime;
};

#endif //NOTIFIER_H
