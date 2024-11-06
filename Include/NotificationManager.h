//
// Created by Amaury Paillard on 06/11/2024.
//

#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Notification.h"

class NotificationManager {
public:
    explicit NotificationManager(const sf::Font& font) : font(font) {

    }

    void addNotification(const std::string& message) {
        sf::Vector2f startPosition(10, static_cast<float>(10 + notifications.size()) * 70);
        notifications.push_back(std::make_shared<Notification>(message, font, startPosition));
    }

    void update(const sf::Time deltaTime) {
        for (const auto& notification : notifications) {
            notification->update(deltaTime);
        }

        notifications.erase(
            std::remove_if(notifications.begin(), notifications.end(),
                           [](const std::shared_ptr<Notification>& notif) { return notif->isExpired(); }),
            notifications.end()
        );

        float yOffset = 10.f;
        for (const auto& notification : notifications) {
            notification->setPosition(sf::Vector2f(10, yOffset));
            yOffset += 70;
        }
    }

    void draw(sf::RenderWindow& window) const {
        for (const auto& notification : notifications) {
            notification->draw(window);
        }
    }

private:
    sf::Font font;
    std::vector<std::shared_ptr<Notification>> notifications;
};


#endif //NOTIFICATIONMANAGER_H
