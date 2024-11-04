//
// Created by Amaury Paillard on 04/11/2024.
//

#include "../include/FontManager.h"

FontManager &FontManager::getInstance() {
    static FontManager instance;
    return instance;
}

sf::Font &FontManager::getFont(const std::string &fontPath) {
    if (const auto it = fonts.find(fontPath); it == fonts.end()) {
        sf::Font font;
        font.loadFromFile(fontPath);
        fonts[fontPath] = font;
    }
    return fonts[fontPath];
}