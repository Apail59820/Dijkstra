//
// Created by Amaury Paillard on 04/11/2024.
//

#ifndef MAP_H
#define MAP_H
#include <vector>

#include "MapPoint.h"

class Map : public sf::Drawable {
public:
    Map();

    std::vector<MapPoint*>* getMap();
    void setMap(const std::vector<MapPoint*>* map);

    void addPoint(const MapPoint& point);
    void removePoint(const MapPoint* point);

    void Update(sf::Vector2f mousePos) const;

    void ProcessEvents(sf::Event& e);

    ~Map() override;

private:

    void cleanupMap();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    std::vector<MapPoint*> map;
    MapPoint* currentDraggedPoint{};
};
#endif //MAP_H
