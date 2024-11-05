//
// Created by Amaury Paillard on 05/11/2024.
//

#include "../include/Route.h"

#include "../include/Globals.h"
#include "../include/Physics.h"


Route::Route(MapPoint *A, MapPoint *B) : route(sf::VertexArray(sf::LinesStrip, 2)) {
    this->startPoint = A;
    this->endPoint = B;

    route[0].color = sf::Color::Green;
    route[1].color = sf::Color::Green;

    distanceText.setCharacterSize(12);
    distanceText.setFillColor(sf::Color::Blue);
    distanceText.setFont(FontManager::getInstance().getFont("../../resources/fonts/Poppins-Regular.ttf"));
}

Route::~Route() = default;

bool Route::isEqual(const MapPoint *A, const MapPoint *B) const {
    return this->startPoint == A && this->endPoint == B;
}

void Route::update() {
    route[0].position = startPoint->getPosition();
    route[1].position = endPoint->getPosition();

    distance = Physics::get_distance(startPoint->getPosition(), endPoint->getPosition());
    distanceText.setString(std::to_string(static_cast<int>(distance)) + "m");

    const sf::Vector2f midPoint = (route[0].position + route[1].position) / 2.f;
    distanceText.setPosition(midPoint);
}

void Route::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(route, states);

    if (Globals::show_distances) {
        target.draw(distanceText, states);
    }
}
