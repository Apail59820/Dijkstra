//
// Created by Amaury Paillard on 05/11/2024.
//

#ifndef DIJKSTRAALGORITHM_H
#define DIJKSTRAALGORITHM_H

#include "MapPoint.h"

class DijkstraAlgorithm {
public:
    DijkstraAlgorithm();
    ~DijkstraAlgorithm();

    static std::vector<MapPoint*> findShortestPath();

};
#endif //DIJKSTRAALGORITHM_H
