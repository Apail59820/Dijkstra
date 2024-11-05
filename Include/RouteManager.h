//
// Created by Amaury Paillard on 04/11/2024.
//

#ifndef ROUTEMANAGER_H
#define ROUTEMANAGER_H
#include "MapPoint.h"
#include "Route.h"

class RouteManager {
public:

    RouteManager();
    ~RouteManager();

    void DrawPointA(MapPoint* point);
    void DrawPointB(MapPoint* point);

    void UpdateRoute();

    void DrawRoutes() const;

    [[nodiscard]] const std::vector<Route>* GetRoutes() const;

    void CancelRouteCreation();

private:
    sf::VertexArray line;

    std::vector<Route> routes;
};

#endif //ROUTEMANAGER_H
