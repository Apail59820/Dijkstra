#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#include "../include/Map.h"
#include "../include/MapPoint.h"

int main() {
    auto window = sf::RenderWindow({1920u, 1080u}, "Dijkstra");
    window.setFramerateLimit(144);
    if (!ImGui::SFML::Init(window))
        return -1;

    sf::Clock clock;

    char mapPointNameInput[12] = {"Point"};

    Map map;
    sf::Vector2i mousePos;

    while (window.isOpen()) {
        mousePos = sf::Mouse::getPosition(window);

        for (auto event = sf::Event(); window.pollEvent(event);) {
            ImGui::SFML::ProcessEvent(window, event);
            map.ProcessEvents(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, clock.restart());

        ImGui::InputText("Name", reinterpret_cast<char *>(&mapPointNameInput), 12, ImGuiInputTextFlags_AutoSelectAll);

        std::cout << mapPointNameInput << std::endl;

        if (ImGui::Button("Add Point")) {
            MapPoint newPoint(mapPointNameInput,
                              sf::Vector2f(static_cast<float>(mousePos.x) - 100, static_cast<float>(mousePos.y)));
            map.addPoint(newPoint);
        }

        ImGui::EndFrame();
        map.Update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

        window.clear(sf::Color::White);
        window.draw(map);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
