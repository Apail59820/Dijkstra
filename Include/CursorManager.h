//
// Created by Amaury Paillard on 04/11/2024.
//

#ifndef CURSORMANAGER_H
#define CURSORMANAGER_H

#include <SFML/Graphics.hpp>

#include "Globals.h"

class CursorManager {
public:
    static CursorManager &getInstance() {
        static CursorManager instance;
        return instance;
    }

    CursorManager(const CursorManager &) = delete;

    CursorManager &operator=(const CursorManager &) = delete;

    bool setCursor(const sf::Cursor::Type cursorType) {
        if (cursor.loadFromSystem(cursorType)) {
            if (Globals::window != nullptr) {
                Globals::window->setMouseCursor(cursor);
            }
            return true;
        }
        return false;
    }

private:
    CursorManager() = default;

    sf::Cursor cursor;
};

#endif //CURSORMANAGER_H
