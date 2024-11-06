//
// Created by Amaury Paillard on 06/11/2024.
//

#include "../include/NotificationManager.h"

#include "../include/FontManager.h"

NotificationManager::NotificationManager() = default;

void NotificationManager::addNotification(const std::string &message) {
    sf::Vector2f startPosition(10, static_cast<float>(10 + notifications.size()) * 70);
    notifications.push_back(std::make_shared<Notification>(
        message, FontManager::getInstance().getFont("../../resources/fonts/Poppins-Regular.ttf"), startPosition));
}

void NotificationManager::update(const sf::Time deltaTime) {
    for (const auto &notification: notifications) {
        notification->update(deltaTime);
    }

    notifications.erase(
        std::remove_if(notifications.begin(), notifications.end(),
                       [](const std::shared_ptr<Notification> &notif) { return notif->isExpired(); }),
        notifications.end()
    );

    float yOffset = 10.f;
    for (const auto &notification: notifications) {
        notification->setPosition(sf::Vector2f(10, yOffset));
        yOffset += 70;
    }
}

void NotificationManager::draw(sf::RenderWindow &window) const {
    for (const auto &notification: notifications) {
        notification->draw(window);
    }
}
