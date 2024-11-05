//
// Created by Amaury Paillard on 05/11/2024.
//

#include "../include/DijkstraAlgorithm.h"

#include "../include/Globals.h"
#include "../include/MapPoint.h"

DijkstraAlgorithm::DijkstraAlgorithm() = default;

DijkstraAlgorithm::~DijkstraAlgorithm() = default;

std::vector<MapPoint *> DijkstraAlgorithm::findShortestPath() {
    MapPoint *start = nullptr;
    MapPoint *end = nullptr;

    for (MapPoint *point: *Globals::map->getMap()) {
        if (point->getIsStartPoint()) {
            start = point;
        }
        if (point->getIsEndPoint()) {
            end = point;
        }
    }

    if (!start || !end) {
        return {};
    }

    std::priority_queue<std::pair<float, MapPoint *>, std::vector<std::pair<float, MapPoint *> >, std::greater<> > pq;
    std::unordered_map<MapPoint *, float> distances;
    std::unordered_map<MapPoint *, MapPoint *> previous;

    for (MapPoint *point: *Globals::map->getMap()) {
        distances[point] = std::numeric_limits<float>::infinity();
    }

    distances[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [currentDistance, currentPoint] = pq.top();
        pq.pop();

        if (currentPoint == end) break;

        for (Route &route: *Globals::route_manager->GetRoutes()) {
            MapPoint *neighbor = nullptr;
            if (route.isEqual(currentPoint, route.getStartPoint()) || route.
                isEqual(currentPoint, route.getEndPoint())) {
                neighbor = route.getEdge(currentPoint);
            }

            if (neighbor) {
                if (float newDist = currentDistance + route.getDistance(); newDist < distances[neighbor]) {
                    distances[neighbor] = newDist;
                    previous[neighbor] = currentPoint;
                    pq.emplace(newDist, neighbor);
                }
            }
        }
    }

    std::vector<MapPoint *> path;
    for (MapPoint *at = end; at != nullptr; at = previous[at]) {
        path.push_back(at);
    }

    std::reverse(path.begin(), path.end());

    if (path.front() == start && !path.empty()) {
        for (size_t i = 0; i < path.size() - 1; ++i) {
            const MapPoint* pointA = path[i];
            const MapPoint* pointB = path[i + 1];

            for (Route &route : *Globals::route_manager->GetRoutes()) {
                if (route.isEqual(pointA, pointB)) {
                    route.setIsPath(true);
                    break;
                }
            }
        }
        return path;
    }
    return {};
}
