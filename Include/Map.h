//
// Created by Amaury Paillard on 04/11/2024.
//

#ifndef MAP_H
#define MAP_H
#include <vector>

#include "MapPoint.h"

class Map final : public sf::Drawable {
public:
    Map();

    std::vector<MapPoint *> *getMap();

    void setMap(const std::vector<MapPoint *> *map);

    void addPoint(const MapPoint &point);

    void removePoint(const MapPoint *point);

    void Update(sf::Vector2f mousePos) const;

    void ProcessEvents(const sf::Event &e);

    ~Map() override;

private:
    void cleanupMap();

    static void HandleRouteSelectionA(MapPoint *point);

    static void HandleRouteSelectionB(MapPoint *point);

    void HandleLeftClick(const sf::Event &e);

    void HandleRightClick(const sf::Event &e) const;

    void HandleMouseReleased(const sf::Event &e);

    static sf::Vector2f GetMousePosition(const sf::Event &e);

    [[nodiscard]] bool ProcessPointForRoute(const sf::Vector2f &mousePos) const;
    [[nodiscard]] bool hasStartPoint() const;
    [[nodiscard]] bool hasEndPoint() const;

    void HandleDrag(MapPoint *point, const sf::Event &e, int i);

    static bool PointInRange(sf::Vector2f mousePos, const MapPoint *point);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    std::vector<MapPoint *> map;
    MapPoint *currentDraggedPoint{};
};
#endif //MAP_H
