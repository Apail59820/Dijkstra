//
// Created by Amaury Paillard on 04/11/2024.
//

#include "../include/Physics.h"
#include "../include/Globals.h"

Physics::Physics() = default;

Physics::~Physics() = default;

float Physics::get_distance(const sf::Vector2f a, const sf::Vector2f b) {
    const float dx = b.x - a.x;
    const float dy = b.y - a.y;
    return std::sqrt(dx * dx + dy * dy);
}

bool Physics::is_overlapping(const MapPoint &object1, const MapPoint &object2) {
    const sf::Vector2f c1 = object1.getPosition();
    const sf::Vector2f c2 = object2.getPosition();
    const float dist = get_distance(c1, c2);

    return dist < object1.getShape()->getRadius() + object2.getShape()->getRadius();
}

void Physics::handleCollision(MapPoint* object1, MapPoint* object2, const float dt) {
    const sf::Vector2f c1 = object1->getPosition();
    const sf::Vector2f c2 = object2->getPosition();

    sf::Vector2f direction = c2 - c1;
    const float distance = get_distance(c1, c2);
    const float overlap = object1->getShape()->getRadius() + object2->getShape()->getRadius() - distance;

    if (distance > 0) {
        direction /= distance;

        const float separationVelocity = overlap * 0.5f;
        object1->velocity -= direction * separationVelocity * dt;
        object2->velocity += direction * separationVelocity * dt;
    }
}

void Physics::update(const sf::Time time) const {
    this->update_physics_sub_steps(static_cast<float>(time.asMilliseconds()), Globals::physic_sub_steps);
}


void Physics::update_physics(const float dt) const {
    for (const auto object: *this->objects) {
        object->applyFriction();

        for (const auto otherObject: *this->objects) {
            if (object != otherObject) {
                if (is_overlapping(*object, *otherObject)) {
                    handleCollision(object, otherObject, dt);
                }
            }
        }

        object->move(dt);
    }
}

void Physics::update_physics_sub_steps(const float dt, const int sub_steps) const {
    const float sub_dt = dt / static_cast<float>(sub_steps);
    for (int i{sub_steps}; i--;) {
        this->update_physics(sub_dt);
    }
}

void Physics::setObjects(std::vector<MapPoint *>*objects) {
    this->objects = objects;
}

std::vector<MapPoint *>*Physics::getObjects() const {
    return this->objects;
}
