#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#include "../include/Globals.h"
#include "../include/Map.h"
#include "../include/MapPoint.h"
#include "../include/Physics.h"

int main() {
    auto window = sf::RenderWindow({1920u, 1080u}, "Dijkstra");
    window.setFramerateLimit(144);
    if (!ImGui::SFML::Init(window))
        return -1;

    sf::Clock clock;
    Physics physics;

    char mapPointNameInput[12] = {"Point"};

    Map map;
    sf::Vector2i mousePos;

    while (window.isOpen()) {
        mousePos = sf::Mouse::getPosition(window);

        if(physics.getObjects() != map.getMap()) {
            physics.setObjects(map.getMap());
        }

        for (auto event = sf::Event(); window.pollEvent(event);) {
            ImGui::SFML::ProcessEvent(window, event);
            map.ProcessEvents(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        const sf::Time dt = clock.restart();
        ImGui::SFML::Update(window, dt);
        physics.update(dt);

        ImGui::InputText("Name", reinterpret_cast<char *>(&mapPointNameInput), 12, ImGuiInputTextFlags_AutoSelectAll);

        if (ImGui::Button("Add Point")) {
            MapPoint newPoint(mapPointNameInput,
                              sf::Vector2f(static_cast<float>(mousePos.x) - 100, static_cast<float>(mousePos.y)));
            map.addPoint(newPoint);
        }

        ImGui::SliderFloat("Friction Coefficient", &Globals::friction_coefficient, 0.0f, 1.0f);
        ImGui::SliderInt("Physics Sub Steps", &Globals::physic_sub_steps, 1, 50);

        ImGui::EndFrame();
        map.Update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

        window.clear(sf::Color::White);
        window.draw(map);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
