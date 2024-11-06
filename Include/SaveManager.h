//
// Created by Amaury Paillard on 06/11/2024.
//

#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H
#include <string>

typedef struct SAVED_POINT {
    int id;
    int x;
    int y;
    std::string name;
    bool isStartPoint;
    bool isEndPoint;
    unsigned long oldPtr;
} SAVED_POINT, P_SAVED_PONT;

typedef struct SAVED_ROUTE {
    int saved_point_a_id;
    int saved_point_b_id;
} SAVED_ROUTE, P_SAVED_ROUTE;

typedef struct SAVE_FILE {
    int point_count;
    int routes_count;

    SAVED_ROUTE *routes;
    SAVED_POINT *points;
} SAVE_FILE, *P_SAVE_FILE;

class SaveManager {
public:

    SaveManager();
    ~SaveManager();

    static void LoadFromFile();
    static void SaveToFile();

private:
    static void saveGraph(const SAVE_FILE& saveFile);
};

#endif //SAVEMANAGER_H
