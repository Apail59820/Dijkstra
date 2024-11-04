//
// Created by Amaury Paillart on 04/11/2024.
//

#include "../Include/Point.h"

#include <SFML/Graphics/RenderTarget.hpp>

void Point::init() {
    this->setRadius(20.0f);
    this->setOrigin(0.5f, 0.5f);

    this->setFillColor(sf::Color::White);
    this->setOutlineColor(sf::Color::Black);
    this->setOutlineThickness(2);
}

Point::Point() {
    init();
}

Point::~Point() = default;




