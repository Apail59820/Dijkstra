//
// Created by Amaury Paillard on 05/11/2024.
//

#include "../include/RouteManager.h"

#include "../include/CursorManager.h"
#include "../include/Globals.h"

RouteManager::RouteManager() : line(sf::VertexArray(sf::LinesStrip, 2)) {
    //CTOR
}

RouteManager::~RouteManager() = default;

void RouteManager::CancelRouteCreation() {
    Globals::is_creating_route = false;

    CursorManager::getInstance().setCursor(sf::Cursor::Arrow);

    Globals::route_point_a = nullptr;
    Globals::route_point_b = nullptr;

    line[0].position = sf::Vector2f(.0f, .0f);
    line[1].position = sf::Vector2f(.0f, .0f);
}


void RouteManager::DrawPointA(MapPoint *point) {
    Globals::route_point_a = point;
    line[0].position = point->getPosition();
    line[0].color = sf::Color::Red;

    const sf::Vector2f mousePosition = Globals::window->mapPixelToCoords(sf::Mouse::getPosition(*Globals::window));
    line[1].position = mousePosition;
    line[1].color = sf::Color::Red;
}

void RouteManager::DrawPointB(MapPoint *point) {
    Globals::route_point_b = point;
    line[1].position = point->getPosition();
    line[1].color = sf::Color::Red;

    for (const Route &route: *Globals::route_manager->GetRoutes()) {
        if (route.isEqual(Globals::route_point_a, Globals::route_point_b)) {
            return CancelRouteCreation();
        }
    }

    const Route new_route(Globals::route_point_a, Globals::route_point_b);
    routes.push_back(new_route);

    CancelRouteCreation();
}

void RouteManager::UpdateRoute() {
    if (Globals::route_point_a != nullptr && Globals::route_point_b == nullptr) {
        const sf::Vector2f mousePosition = Globals::window->mapPixelToCoords(sf::Mouse::getPosition(*Globals::window));
        line[1].position = mousePosition;
    }

    for (Route &route: routes) {
        route.update();
    }

    Globals::route_amount = routes.size();
}


void RouteManager::DrawRoutes() const {
    if (Globals::is_creating_route) {
        Globals::window->draw(line);
    }

    for (const Route &route: routes) {
        Globals::window->draw(route);
    }
}

const std::vector<Route> *RouteManager::GetRoutes() const {
    return &this->routes;
}
