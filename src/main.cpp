#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#include "../include/CursorManager.h"
#include "../include/Globals.h"
#include "../include/Map.h"
#include "../include/Physics.h"
#include "../include/Gui.h"

int main() {
    Globals::window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "Dijkstra");
    Globals::route_manager = std::make_unique<RouteManager>();
    Globals::map = std::make_unique<Map>();
    Globals::physics = std::make_unique<Physics>();
    Globals::notification_manager = std::make_unique<NotificationManager>(FontManager::getInstance().getFont("../../resources/fonts/Poppins-Regular.ttf"));

    Globals::window->setFramerateLimit(144);
    if (!ImGui::SFML::Init(*Globals::window))
        return -1;

    sf::Clock clock;

    while (Globals::window->isOpen()) {
        if(Globals::physics->getObjects() != Globals::map->getMap()) {
            Globals::physics->setObjects(Globals::map->getMap());
        }

        for (auto event = sf::Event(); Globals::window->pollEvent(event);) {
            ImGui::SFML::ProcessEvent(*Globals::window, event);
            Globals::map->ProcessEvents(event);

            if (event.type == sf::Event::Closed) {
                Globals::window->close();
            }
        }

        const sf::Time dt = clock.restart();

        ImGui::SFML::Update(*Globals::window, dt);
        Globals::route_manager->UpdateRoute();
        Globals::physics->update(dt);
        Globals::notification_manager->update(dt);

        if(Globals::is_creating_route) {
            CursorManager::getInstance().setCursor(sf::Cursor::Cross);
        }

        Gui::Render();

        ImGui::EndFrame();

        Globals::map->Update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*Globals::window)));

        Globals::window->clear(sf::Color::White);

        Globals::route_manager->DrawRoutes();
        Globals::window->draw(*Globals::map);

        ImGui::SFML::Render(*Globals::window);

        Globals::notification_manager->draw(*Globals::window);

        Globals::window->display();

    }

    ImGui::SFML::Shutdown();
    Globals::window.reset();

    return 0;
}
