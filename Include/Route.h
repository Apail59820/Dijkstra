//
// Created by Amaury Paillard on 05/11/2024.
//

#ifndef ROUTE_H
#define ROUTE_H
#include "MapPoint.h"

class Route final : public sf::Drawable {

public:

    Route(MapPoint* A, MapPoint* B);
    ~Route() override;

    void update();

    bool isEqual(const MapPoint* A, const MapPoint* B) const;

private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    MapPoint*startPoint = nullptr;
    MapPoint*endPoint = nullptr;

    sf::VertexArray route;
};
#endif //ROUTE_H
