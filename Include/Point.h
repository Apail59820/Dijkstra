//
// Created by Amaury Paillart on 04/11/2024.
//

#ifndef POINT_H
#define POINT_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>

class Point : public sf::CircleShape {
    public:

    Point();

    ~Point() override;

    private:
    void init();
};
#endif //POINT_H
