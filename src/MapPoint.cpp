//
// Created by Amaury Paillard on 04/11/2024.
//

#include "../include/MapPoint.h"

#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>
#include <__filesystem/operations.h>
#include <__filesystem/path.h>

void MapPoint::init() {
    circle.setRadius(20.0f);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setFillColor(sf::Color::White);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(2);

    if (!this->name.empty()) {
        LoadTextName();
    }
}

MapPoint::MapPoint() {
    init();
}

MapPoint::MapPoint(std::string name) : name(std::move(name)) {
    init();
    LoadTextName();
}

MapPoint::MapPoint(const std::string &name, const sf::Vector2f position) {
    this->name = name;
    this->circle.setPosition(position);
    init();
}

sf::Vector2f MapPoint::getPosition() const {
    return circle.getPosition();
}

void MapPoint::setPosition(const sf::Vector2f position) {
    circle.setPosition(position);
}

void MapPoint::LoadTextName() {
    nameText.setString(name);
    std::filesystem::path path = std::filesystem::current_path();
    std::cout << path << std::endl;
    nameText.setFont(FontManager::getInstance().getFont("../../resources/fonts/Poppins-Regular.ttf"));
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

void MapPoint::Update(const sf::Vector2f &mousePosition) {
    if (isDragging) {
        setPosition(mousePosition);
        LoadTextName();
    }
}

void MapPoint::StartDragging(const sf::Vector2f &mousePosition) {
    isDragging = true;
    dragOffset = mousePosition - circle.getPosition();
}

void MapPoint::StopDragging() {
    isDragging = false;
}

const sf::CircleShape *MapPoint::getShape() const {
    return &this->circle;
}


void MapPoint::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(circle, states);
    target.draw(nameText, states);
}

MapPoint::~MapPoint() = default;