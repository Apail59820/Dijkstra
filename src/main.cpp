#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#include "../include/CursorManager.h"
#include "../include/Globals.h"
#include "../include/Map.h"
#include "../include/MapPoint.h"
#include "../include/Physics.h"

int main() {
    Globals::window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "Dijkstra");

    RouteManager routeManager;
    Globals::route_manager = std::make_unique<RouteManager>(routeManager);

    Globals::window->setFramerateLimit(144);
    if (!ImGui::SFML::Init(*Globals::window))
        return -1;

    sf::Clock clock;
    Physics physics;

    char mapPointNameInput[12] = {"Point"};

    Map map;

    while (Globals::window->isOpen()) {
        const sf::Vector2i mousePos = sf::Mouse::getPosition(*Globals::window);

        if(physics.getObjects() != map.getMap()) {
            physics.setObjects(map.getMap());
        }

        for (auto event = sf::Event(); Globals::window->pollEvent(event);) {
            ImGui::SFML::ProcessEvent(*Globals::window, event);
            map.ProcessEvents(event);

            if (event.type == sf::Event::Closed) {
                Globals::window->close();
            }
        }

        const sf::Time dt = clock.restart();
        ImGui::SFML::Update(*Globals::window, dt);
        Globals::route_manager->UpdateRoute();
        physics.update(dt);

        ImGui::InputText("Name", reinterpret_cast<char *>(&mapPointNameInput), 12, ImGuiInputTextFlags_AutoSelectAll);

        if (ImGui::Button("Add Point")) {
            MapPoint newPoint(mapPointNameInput,
                              sf::Vector2f(static_cast<float>(mousePos.x) - 100, static_cast<float>(mousePos.y)));
            map.addPoint(newPoint);
        }

        if(ImGui::Button("Create Route")) {
            CursorManager::getInstance().setCursor(sf::Cursor::Cross);
            Globals::is_creating_route = true;
        }

        ImGui::SliderFloat("Friction Coefficient", &Globals::friction_coefficient, 0.0f, 1.0f);
        ImGui::SliderInt("Physics Sub Steps", &Globals::physic_sub_steps, 1, 50);
        ImGui::Text("Routes : %i", Globals::route_amount);

        ImGui::EndFrame();
        map.Update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*Globals::window)));

        Globals::window->clear(sf::Color::White);

        Globals::route_manager->DrawRoutes();
        Globals::window->draw(map);

        ImGui::SFML::Render(*Globals::window);
        Globals::window->display();

    }

    ImGui::SFML::Shutdown();
    Globals::window.reset();

    return 0;
}
