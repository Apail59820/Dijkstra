//
// Created by Amaury Paillard on 04/11/2024.
//

#ifndef PHYSICS_H
#define PHYSICS_H
#include <vector>

#include "MapPoint.h"

class Physics {
public:
    Physics();

    ~Physics();

    [[nodiscard]] std::vector<MapPoint *>*getObjects() const;

    void setObjects(std::vector<MapPoint *>*objects);

    void update(sf::Time time) const;

private:
    static float get_distance(sf::Vector2f a, sf::Vector2f b);

    static bool is_overlapping(const MapPoint &object1, const MapPoint &object2);

    static void handleCollision(MapPoint* object1, MapPoint* object2, float dt);

    void update_physics_sub_steps(float dt, int sub_steps) const;

    void update_physics(float dt) const;

    std::vector<MapPoint *>* objects;
};

#endif //PHYSICS_H
