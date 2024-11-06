//
// Created by Amaury Paillard on 06/11/2024.
//

#include "../include/SaveManager.h"

#include <fstream>

#include "../include/Globals.h"

SaveManager::SaveManager() = default;

SaveManager::~SaveManager() = default;

void SaveManager::LoadFromFile() {
    const auto filename = "graph_data.bin";

    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        return;
    }

    SAVE_FILE saveFile;

    inFile.read(reinterpret_cast<char *>(&saveFile.point_count), sizeof(saveFile.point_count));
    inFile.read(reinterpret_cast<char *>(&saveFile.routes_count), sizeof(saveFile.routes_count));

    saveFile.points = new SAVED_POINT[saveFile.point_count];
    saveFile.routes = new SAVED_ROUTE[saveFile.routes_count];

    for (int i = 0; i < saveFile.point_count; ++i) {
        inFile.read(reinterpret_cast<char *>(&saveFile.points[i]), sizeof(SAVED_POINT));
    }

    for (int i = 0; i < saveFile.routes_count; ++i) {
        inFile.read(reinterpret_cast<char *>(&saveFile.routes[i]), sizeof(SAVED_ROUTE));
    }

    if (!inFile.good()) {
        delete[] saveFile.points;
        delete[] saveFile.routes;
        return;
    }

    inFile.close();

    Globals::map->getMap()->clear();
    Globals::route_manager->GetRoutes()->clear();

    std::vector<MapPoint *> loadedPoints;

    for (int i = 0; i < saveFile.point_count; ++i) {
        const auto &[id, x, y, name, isStartPoint, isEndPoint, oldPtr] = saveFile.points[i];

        auto new_point = new MapPoint(
            name, sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
        new_point->setIsEndPoint(isEndPoint);
        new_point->setIsStartPoint(isStartPoint);

        Globals::map->addPoint(*new_point);
        loadedPoints.push_back(new_point);
    }

    for (int i = 0; i < saveFile.routes_count; ++i) {
        if (const auto &[saved_point_a_id, saved_point_b_id] = saveFile.routes[i];
            saved_point_a_id < saveFile.point_count && saved_point_b_id < saveFile.point_count) {
            MapPoint *startPoint = loadedPoints[saved_point_a_id];

            if (MapPoint *endPoint = loadedPoints[saved_point_b_id]; startPoint && endPoint) {
                const auto *newRoute = new Route(startPoint, endPoint);
                Globals::route_manager->AddRoute(newRoute);
            }
        }
    }

    
    delete[] saveFile.points;
    delete[] saveFile.routes;
}

void SaveManager::SaveToFile() {
    const int pointsCount = static_cast<int>(Globals::map->getMap()->size());
    SAVED_POINT pointsToSave[pointsCount];

    for (int i = 0; i < pointsCount; i++) {
        const MapPoint map_point = *Globals::map->getMap()->at(i);
        SAVED_POINT pointToSave = {
            i,
            static_cast<int>(map_point.getPosition().x),
            static_cast<int>(map_point.getPosition().y),
            map_point.getName(),
            map_point.getIsStartPoint(),
            map_point.getIsEndPoint(),
            reinterpret_cast<unsigned long>(Globals::map->getMap()->at(i))
        };
        pointsToSave[i] = pointToSave;
    }

    const int routesCount = static_cast<int>(Globals::route_manager->GetRoutes()->size());
    SAVED_ROUTE routesToSave[routesCount];

    for (int i = 0; i < routesCount; i++) {
        const Route route = Globals::route_manager->GetRoutes()->at(i);

        const MapPoint *startPoint = route.getStartPoint();
        const MapPoint *endPoint = route.getEndPoint();

        int startId = -1;
        int endId = -1;

        for (int j = 0; j < pointsCount; j++) {
            if (pointsToSave[j].oldPtr == reinterpret_cast<unsigned long>(startPoint)) {
                startId = pointsToSave[j].id;
                break;
            }
        }

        for (int j = 0; j < pointsCount; j++) {
            if (pointsToSave[j].oldPtr == reinterpret_cast<unsigned long>(endPoint)) {
                endId = pointsToSave[j].id;
                break;
            }
        }

        if (startId != -1 && endId != -1) {
            routesToSave[i] = {startId, endId};
        }
    }

    SAVE_FILE saveFile;
    saveFile.point_count = pointsCount;
    saveFile.routes_count = routesCount;

    saveFile.points = new SAVED_POINT[pointsCount];
    saveFile.routes = new SAVED_ROUTE[routesCount];

    for (int i = 0; i < pointsCount; i++) {
        saveFile.points[i] = pointsToSave[i];
    }

    for (int i = 0; i < routesCount; i++) {
        saveFile.routes[i] = routesToSave[i];
    }

    saveGraph(saveFile);

    delete[] saveFile.points;
    delete[] saveFile.routes;
}

void SaveManager::saveGraph(const SAVE_FILE &saveFile) {
    const auto filename = "graph_data.bin";

    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        return;
    }

    outFile.write(reinterpret_cast<const char *>(&saveFile.point_count), sizeof(saveFile.point_count));
    outFile.write(reinterpret_cast<const char *>(&saveFile.routes_count), sizeof(saveFile.routes_count));

    for (int i = 0; i < saveFile.point_count; ++i) {
        outFile.write(reinterpret_cast<const char *>(&saveFile.points[i]), sizeof(SAVED_POINT));
    }

    for (int i = 0; i < saveFile.routes_count; ++i) {
        outFile.write(reinterpret_cast<const char *>(&saveFile.routes[i]), sizeof(SAVED_ROUTE));
    }

    outFile.close();
}
