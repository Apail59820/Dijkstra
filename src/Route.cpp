//
// Created by Amaury Paillard on 05/11/2024.
//

#include "../include/Route.h"


Route::Route(MapPoint *A, MapPoint *B) : route(sf::VertexArray(sf::LinesStrip, 2)) {
    this->startPoint = A;
    this->endPoint = B;

    route[0].color = sf::Color::Green;
    route[1].color = sf::Color::Green;
}

Route::~Route() = default;

bool Route::isEqual(const MapPoint *A, const MapPoint *B) const {
    return this->startPoint == A && this->endPoint == B;
}

void Route::update() {
    route[0].position = startPoint->getPosition();
    route[1].position = endPoint->getPosition();
}

void Route::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(route, states);
}



