//
// Created by Amaury Paillard on 04/11/2024.
//

#include "../include/MapPoint.h"

#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>
#include <__filesystem/operations.h>
#include <__filesystem/path.h>

#include "../include/CursorManager.h"
#include "../include/Globals.h"

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
    nameText.setFont(FontManager::getInstance().getFont("../../resources/fonts/Poppins-Regular.ttf"));
    nameText.setCharacterSize(24);
    nameText.setFillColor(sf::Color::Black);


    AdjustRadiusForText();

    nameText.setPosition(circle.getPosition().x, circle.getPosition().y);
}

void MapPoint::Update(const sf::Vector2f &mousePosition) {
    if (isDragging) {
        setPosition(mousePosition);
        LoadTextName();
    }


    if (isHovered) {
        if (!Globals::is_creating_route) {
            CursorManager::getInstance().setCursor(sf::Cursor::Hand);
        }
        circle.setFillColor(sf::Color::Cyan);
    } else {
        if (!Globals::is_creating_route) {
            CursorManager::getInstance().setCursor(sf::Cursor::Arrow);
        }

        if (isStartPoint) {
            circle.setFillColor(sf::Color::Green);
        } else if (isEndPoint) {
            circle.setFillColor(sf::Color::Yellow);
        } else if(isPath) {
            circle.setFillColor(sf::Color::Magenta);
        }
        else {
            circle.setFillColor(sf::Color::White);
        }
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

void MapPoint::setPos(const sf::Vector2f &position) {
    circle.setPosition(position);
    nameText.setPosition(position);
}

void MapPoint::applyFriction() {
    velocity *= Globals::friction_coefficient;
}

void MapPoint::move(const float dt) {
    setPos(getPosition() + velocity * dt);
}

void MapPoint::setIsHovered(const bool hoverState) {
    isHovered = hoverState;
}

bool MapPoint::getIsHovered() const {
    return isHovered;
}

void MapPoint::setIsStartPoint(const bool bState) {
    isStartPoint = bState;
    if (bState) {
        circle.setPointCount(6);
    } else {
        circle.setPointCount(30);
    }

    AdjustRadiusForText();
}

void MapPoint::setIsEndPoint(const bool bState) {
    isEndPoint = bState;
    if (bState) {
        circle.setPointCount(4);
    } else {
        circle.setPointCount(30);
    }

    AdjustRadiusForText();
}

void MapPoint::AdjustRadiusForText() {
    nameTextLocalBounds = nameText.getLocalBounds();
    const float textWidth = nameTextLocalBounds.width;

    const float newRadius = std::max(textWidth / 2.0f + 10.0f, circle.getRadius());

    circle.setRadius(newRadius);
    circle.setOrigin(newRadius, newRadius);

    nameText.setOrigin(nameTextLocalBounds.left + nameTextLocalBounds.width / 2.0f,
                       nameTextLocalBounds.top + nameTextLocalBounds.height / 2.0f);
    nameText.setPosition(circle.getPosition());
}

bool MapPoint::getIsStartPoint() const {
    return isStartPoint;
}

bool MapPoint::getIsEndPoint() const {
    return isEndPoint;
}

std::string MapPoint::getName() const {
    return name;
}

void MapPoint::setAsPath() {
    isPath = true;
}

MapPoint::~MapPoint() = default;
