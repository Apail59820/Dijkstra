//
// Created by Amaury Paillard on 04/11/2024.
//

#ifndef POINT_H
#define POINT_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "FontManager.h"

#include <iostream>

class MapPoint final : public sf::Drawable {
public:
    MapPoint();

    explicit MapPoint(std::string name);

    MapPoint(const std::string &name, sf::Vector2f position);

    void setPosition(sf::Vector2f position);

    sf::Vector2f getPosition() const;

    void Update(const sf::Vector2f &mousePosition);

    void StartDragging(const sf::Vector2f &mousePosition);

    void StopDragging();

    const sf::CircleShape *getShape() const;

    ~MapPoint() override;

private:
    void init();

    void LoadTextName();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    std::string name;
    sf::CircleShape circle;
    sf::Text nameText;
    sf::FloatRect nameTextLocalBounds;

    bool isDragging = false;
    sf::Vector2f dragOffset;
};

#endif //POINT_H