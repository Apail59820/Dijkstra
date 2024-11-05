//
// Created by Amaury Paillard on 04/11/2024.
//

#include "../include/Map.h"

#include "../include/Globals.h"

Map::Map() = default;

std::vector<MapPoint *> *Map::getMap() {
    return &this->map;
}

void Map::cleanupMap() {
    for (const MapPoint *point: map) {
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

void Map::Update(const sf::Vector2f mousePos) const {
    for (MapPoint *point: map) {
        point->Update(mousePos);
    }
}


bool Map::PointInRange(const sf::Vector2f mousePos, const MapPoint *point) {
    return point->getShape()->getGlobalBounds().contains(mousePos);
}

void Map::ProcessEvents(const sf::Event &e) {
    if (e.type == sf::Event::MouseButtonPressed) {
        if (e.mouseButton.button == sf::Mouse::Left) {
            const auto mousePos = sf::Vector2f(static_cast<float>(e.mouseButton.x),
                                               static_cast<float>(e.mouseButton.y));
            for (size_t i = map.size(); i > 0; --i) {
                if (MapPoint *point = map[i - 1]; Globals::is_creating_route && PointInRange(mousePos, point)) {
                    HandleRouteSelectionA(point);
                } else {
                    HandleDrag(point, e, static_cast<int>(i));
                }
            }
        }
    }
    if (e.type == sf::Event::MouseButtonReleased) {
        if (e.mouseButton.button == sf::Mouse::Left) {
            if (Globals::is_creating_route) {
                const auto mousePos = sf::Vector2f(static_cast<float>(e.mouseButton.x),
                                                   static_cast<float>(e.mouseButton.y));
                for (size_t i = map.size(); i > 0; --i) {
                    if (MapPoint *point = map[i - 1]; Globals::is_creating_route && PointInRange(mousePos, point)) {
                        HandleRouteSelectionB(point);
                    }
                }
            }

            if (!Globals::is_creating_route && currentDraggedPoint != nullptr) {
                currentDraggedPoint->StopDragging();
                currentDraggedPoint = nullptr;
            }
        }
    }
}

void Map::HandleDrag(MapPoint *point, const sf::Event &e, const int i) {
    const auto mousePos = sf::Vector2f(static_cast<float>(e.mouseButton.x),
                                       static_cast<float>(e.mouseButton.y));
    if (PointInRange(mousePos, point)) {
        if (currentDraggedPoint == nullptr) {
            point->StartDragging(mousePos);
            currentDraggedPoint = point;

            // Move to front
            map.erase(map.begin() + (i - 1));
            map.push_back(currentDraggedPoint);
        }
    }
}

void Map::HandleRouteSelectionA(MapPoint *point) {
    if (Globals::route_point_a == nullptr) {
        Globals::route_manager->DrawPointA(point);
    }
}

void Map::HandleRouteSelectionB(MapPoint *point) {
    if (Globals::route_point_b == nullptr) {
        Globals::route_manager->DrawPointB(point);
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
