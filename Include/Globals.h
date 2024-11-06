//
// Created by Amaury Paillard on 04/11/2024.
//

#ifndef GLOBALS_H
#define GLOBALS_H
#include "Map.h"
#include "MapPoint.h"
#include "NotificationManager.h"
#include "Physics.h"
#include "RouteManager.h"

namespace Globals {
    inline int physic_sub_steps = 12;
    inline float friction_coefficient = 0.845f;

    inline bool is_creating_route = false;
    inline bool is_creating_start_point = false;
    inline bool is_creating_end_point = false;
    inline bool is_adding_point = false;

    inline MapPoint* route_point_a = nullptr;
    inline MapPoint* route_point_b = nullptr;

    inline std::unique_ptr<sf::RenderWindow> window;
    inline std::unique_ptr<RouteManager> route_manager;
    inline std::unique_ptr<Map> map;
    inline std::unique_ptr<Physics> physics;
    inline std::unique_ptr<NotificationManager> notification_manager;

    inline unsigned int route_amount = 0;
    inline bool auto_name = true;

    inline bool show_distances = true;

    inline char mapPointNameInput[12] = {"Point"};
}

#endif //GLOBALS_H
