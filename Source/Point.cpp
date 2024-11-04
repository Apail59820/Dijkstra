#include "../Include/Point.h"

#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>

void Point::init() {
    circle.setRadius(20.0f);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setFillColor(sf::Color::White);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(2);
}

Point::Point() {
    init();
}

Point::Point(std::string name) : name(std::move(name)) {
    init();
    LoadTextName();
}

Point::Point(const std::string &name, const sf::Vector2f position) {
    init();
    this->name = name;
    this->circle.setPosition(position);
}

sf::Vector2f Point::getPosition() const {
    return circle.getPosition();
}

void Point::setPosition(const sf::Vector2f position) {
    circle.setPosition(position);
    if (!this->name.empty()) {
        LoadTextName();
    }
}

void Point::LoadTextName() {
    nameText.setString(name);
    nameText.setFont(FontManager::getInstance().getFont("../Resources/fonts/Poppins-Regular.ttf"));
    nameText.setCharacterSize(24);
    nameText.setFillColor(sf::Color::Black);

    nameTextLocalBounds = nameText.getLocalBounds();
    nameText.setOrigin(nameTextLocalBounds.left + nameTextLocalBounds.width / 2.0f,
                       nameTextLocalBounds.top + nameTextLocalBounds.height / 2.0f);

    const float textWidth = nameTextLocalBounds.width;

    const float newRadius = std::max(textWidth / 2.0f + 10.0f, circle.getRadius());
    circle.setRadius(newRadius);
    circle.setOrigin(newRadius, newRadius);

    nameText.setPosition(circle.getPosition().x, circle.getPosition().y);
}

void Point::Update(const sf::Vector2f &mousePosition) {
    if (isDragging) {
        setPosition(mousePosition);
        LoadTextName();
    }
}

void Point::StartDragging(const sf::Vector2f &mousePosition) {
    isDragging = true;
    dragOffset = mousePosition - circle.getPosition();
}

void Point::StopDragging() {
    isDragging = false;
}

const sf::CircleShape *Point::getShape() const {
    return &this->circle;
}


void Point::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(circle, states);
    target.draw(nameText, states);
}

Point::~Point() = default;
