//
// Created by Amaury Paillard on 04/11/2024.
//

#include "../include/Map.h"

Map::Map() = default;

std::vector<MapPoint *> *Map::getMap() {
    return &this->map;
}

void Map::cleanupMap() {
    for (MapPoint *point: map) {
        delete point;
    }
    map.clear();
}

void Map::addPoint(const MapPoint &point) {
    map.push_back(new MapPoint(point));
}

void Map::removePoint(const MapPoint *point) {
    auto it = std::remove_if(map.begin(), map.end(),
                             [point](const MapPoint *p) { return p == point; });

    for (auto iter = it; iter != map.end(); ++iter) {
        delete *iter;
    }

    map.erase(it, map.end());
}

void Map::setMap(const std::vector<MapPoint *> *map) {
    if (!this->map.empty()) {
        cleanupMap();
    }
    this->map = *map;
}

void Map::Update(sf::Vector2f mousePos) const {
    for (MapPoint *point: map) {
        point->Update(mousePos);
    }
}

void Map::ProcessEvents(sf::Event &e) {
    if (e.type == sf::Event::MouseButtonPressed) {
        if (e.mouseButton.button == sf::Mouse::Left) {
            for (MapPoint *point: map) {
                if (const auto mousePos = sf::Vector2f(static_cast<float>(e.mouseButton.x),
                                                       static_cast<float>(e.mouseButton.y)); point->getShape()->
                    getGlobalBounds().contains(mousePos)) {
                    point->StartDragging(mousePos);
                    currentDraggedPoint = point;
                }
            }
        }
    }
    if (e.type == sf::Event::MouseButtonReleased) {
        if (e.mouseButton.button == sf::Mouse::Left && currentDraggedPoint != nullptr) {
            currentDraggedPoint->StopDragging();
            currentDraggedPoint = nullptr;
        }
    }
}


void Map::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    for (const MapPoint *point: map) {
        target.draw(*point, states);
    }
}

Map::~Map() {
    this->cleanupMap();
}
