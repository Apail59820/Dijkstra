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
    const auto it = std::remove_if(map.begin(), map.end(),
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
        if (PointInRange(mousePos, point)) {
            point->setIsHovered(true);
        } else {
            if (point->getIsHovered()) {
                point->setIsHovered(false);
            }
        }
    }
}


bool Map::PointInRange(const sf::Vector2f mousePos, const MapPoint *point) {
    return point->getShape()->getGlobalBounds().contains(mousePos);
}

void Map::ProcessEvents(const sf::Event &e) {
    if (e.type == sf::Event::MouseButtonPressed) {
        if (e.mouseButton.button == sf::Mouse::Left) {
            HandleLeftClick(e);
        } else if (e.mouseButton.button == sf::Mouse::Right) {
            HandleRightClick(e);
        }
    } else if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left) {
        HandleMouseReleased(e);
    }
}

void Map::HandleLeftClick(const sf::Event &e) {
    const sf::Vector2f mousePos = GetMousePosition(e);

    for (size_t i = map.size(); i > 0; --i) {
        if (MapPoint *point = map[i - 1]; Globals::is_creating_route && PointInRange(mousePos, point)) {
            HandleRouteSelectionA(point);
            return;
        } else {
            HandleDrag(point, e, static_cast<int>(i));
        }
    }
}

void Map::HandleRightClick(const sf::Event &e) const {
    const sf::Vector2f mousePos = GetMousePosition(e);

    for (size_t i = map.size(); i > 0; --i) {
        MapPoint *point = map[i - 1];
        if (Globals::is_creating_start_point && PointInRange(mousePos, point)) {
            if (hasStartPoint()) {
                for (MapPoint *p: map) {
                    if (p->getIsStartPoint()) {
                        p->setIsStartPoint(false);
                    }
                }
            }
            point->setIsStartPoint(true);
            Globals::is_creating_start_point = false;
            return;
        }

        if (Globals::is_creating_end_point && PointInRange(mousePos, point)) {
            if (hasEndPoint()) {
                for (MapPoint *p: map) {
                    if (p->getIsEndPoint()) {
                        p->setIsEndPoint(false);
                    }
                }
            }
            point->setIsEndPoint(true);
            Globals::is_creating_end_point = false;
            return;
        }
    }
}

void Map::HandleMouseReleased(const sf::Event &e) {
    const sf::Vector2f mousePos = GetMousePosition(e);

    if (Globals::is_creating_route) {
        if (!ProcessPointForRoute(mousePos)) {
            Globals::route_manager->CancelRouteCreation();
        }
    } else if (currentDraggedPoint != nullptr) {
        currentDraggedPoint->StopDragging();
        currentDraggedPoint = nullptr;
    }
}

sf::Vector2f Map::GetMousePosition(const sf::Event &e) {
    return {static_cast<float>(e.mouseButton.x), static_cast<float>(e.mouseButton.y)};
}

bool Map::ProcessPointForRoute(const sf::Vector2f &mousePos) const {
    for (size_t i = map.size(); i > 0; --i) {
        if (MapPoint *point = map[i - 1]; PointInRange(mousePos, point)) {
            HandleRouteSelectionB(point);
            return true;
        }
    }
    return false;
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

bool Map::hasStartPoint() const {
    return std::any_of(map.begin(), map.end(), [](const MapPoint *point) {
        return point->getIsStartPoint();
    });
}

bool Map::hasEndPoint() const {
    return std::any_of(map.begin(), map.end(), [](const MapPoint *point) {
        return point->getIsEndPoint();
    });
}

Map::~Map() {
    this->cleanupMap();
}
