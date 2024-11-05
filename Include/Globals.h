//
// Created by Amaury Paillard on 04/11/2024.
//

#ifndef GLOBALS_H
#define GLOBALS_H
#include "MapPoint.h"
#include "RouteManager.h"

namespace Globals {
    inline int physic_sub_steps = 12;
    inline float friction_coefficient = 0.845f;
    inline bool is_creating_route = false;

    inline MapPoint* route_point_a = nullptr;
    inline MapPoint* route_point_b = nullptr;

    inline std::unique_ptr<sf::RenderWindow> window;
    inline std::unique_ptr<RouteManager> route_manager;

    inline unsigned int route_amount = 0;

    inline bool show_distances = true;
}

#endif //GLOBALS_H
