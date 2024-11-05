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
    return (startPoint == A && endPoint == B) || (startPoint == B && endPoint == A);
}

MapPoint *Route::getEdge(const MapPoint *otherEdge) const {
    if (startPoint == otherEdge) {
        return endPoint;
    }
    return startPoint;
}

void Route::update() {
    route[0].position = startPoint->getPosition();
    route[1].position = endPoint->getPosition();

    distance = Physics::get_distance(startPoint->getPosition(), endPoint->getPosition());
    distanceText.setString(std::to_string(static_cast<int>(distance)) + "m");

    const sf::Vector2f midPoint = (route[0].position + route[1].position) / 2.f;
    distanceText.setPosition(midPoint);

    if(isPath) {
        route[0].color = sf::Color::Magenta;
        route[1].color = sf::Color::Magenta;
    } else {
        route[0].color = sf::Color::Black;
        route[1].color = sf::Color::Black;
    }
}

void Route::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(route, states);

    if (Globals::show_distances) {
        target.draw(distanceText, states);
    }
}

MapPoint *Route::getStartPoint() const {
    return startPoint;
}

MapPoint *Route::getEndPoint() const {
    return endPoint;
}

float Route::getDistance() const {
    return distance;
}

void Route::setIsPath(const bool bState) {
    isPath = bState;
}

