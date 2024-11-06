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
    NotificationManager();

    void addNotification(const std::string &message);

    void update(sf::Time deltaTime);

    void draw(sf::RenderWindow &window) const;

private:
    std::vector<std::shared_ptr<Notification> > notifications;
};


#endif //NOTIFICATIONMANAGER_H
