//
// Created by Amaury Paillard on 06/11/2024.
//


#include "../include/Notification.h"

Notification::Notification(const std::string &message, const sf::Font &font,
                           const sf::Vector2f position) : duration(sf::seconds(3)), elapsedTime(sf::Time::Zero) {
    text.setFont(font);
    text.setString(message);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(position);

    background.setSize(sf::Vector2f(text.getLocalBounds().width + 20, text.getLocalBounds().height + 20));
    background.setFillColor(sf::Color(0, 0, 0, 180));
    background.setPosition(position.x - 10, position.y - 10);
}

void Notification::update(const sf::Time &dt) {
    elapsedTime += dt;
    if (elapsedTime < sf::seconds(0.5f)) {
        const float progress = elapsedTime / sf::seconds(0.5f);
        const float yOffset = -50.0f * (1 - progress);
        text.move(0, yOffset);
        background.move(0, yOffset);
    }
}

bool Notification::isExpired() const {
    return elapsedTime >= duration;
}

void Notification::setPosition(const sf::Vector2f newPosition) {
    text.setPosition(newPosition);
    background.setPosition(newPosition.x - 10, newPosition.y - 10);
}

void Notification::draw(sf::RenderWindow &window) const {
    window.draw(background);
    window.draw(text);
}
