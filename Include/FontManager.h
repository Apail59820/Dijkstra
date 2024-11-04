//
// Created by Amaury Paillart on 04/11/2024.
//

#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class FontManager {
public:
    static FontManager& getInstance();

    sf::Font& getFont(const std::string& fontPath);

    FontManager(const FontManager&) = delete;
    FontManager& operator=(const FontManager&) = delete;

private:
    FontManager() = default;
    std::unordered_map<std::string, sf::Font> fonts;
};

#endif //FONTMANAGER_H
