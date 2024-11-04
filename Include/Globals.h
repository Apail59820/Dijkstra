//
// Created by Amaury Paillard on 04/11/2024.
//

#ifndef GLOBALS_H
#define GLOBALS_H
#include "MapPoint.h"

namespace Globals {
    inline int physic_sub_steps = 8;
    inline float friction_coefficient = 0.5f;
    inline bool is_creating_route = false;

    inline MapPoint* route_point_a = nullptr;
    inline MapPoint* route_point_b = nullptr;

    inline std::unique_ptr<sf::RenderWindow> window;
}

#endif //GLOBALS_H
