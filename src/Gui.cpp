//
// Created by Amaury Paillard on 05/11/2024.
//

#include "../include/Gui.h"
#include <imgui-SFML.h>
#include <imgui.h>

#include "../include/DijkstraAlgorithm.h"
#include "../include/MapPoint.h"
#include "../include/Globals.h"

Gui::Gui() = default;
Gui::~Gui() = default;



void Gui::Render() {
    const sf::Vector2i mousePos = sf::Mouse::getPosition(*Globals::window);

    ImGui::InputText("Name", reinterpret_cast<char *>(&mapPointNameInput), 12, ImGuiInputTextFlags_AutoSelectAll);

    if (ImGui::Button("Add Point")) {
        const MapPoint newPoint(mapPointNameInput,
                                sf::Vector2f(static_cast<float>(mousePos.x) - 100, static_cast<float>(mousePos.y)));
        Globals::map->addPoint(newPoint);
    }

    if(ImGui::Button("Create Route")) {
        Globals::is_creating_route = true;
        Globals::is_creating_end_point = false;
        Globals::is_creating_start_point = false;
    }

    ImGui::SliderFloat("Friction Coefficient", &Globals::friction_coefficient, 0.0f, 1.0f);
    ImGui::SliderInt("Physics Sub Steps", &Globals::physic_sub_steps, 1, 50);
    ImGui::Text("Routes : %i", Globals::route_amount);
    ImGui::Checkbox("Show Distances", &Globals::show_distances);

    if(ImGui::Button("Set Start Point")) {
        Globals::is_creating_route = false;
        Globals::is_creating_end_point = false;
        Globals::is_creating_start_point = true;
    }

    ImGui::SameLine();

    if(ImGui::Button("Set End Point")) {
        Globals::is_creating_route = false;
        Globals::is_creating_start_point = false;
        Globals::is_creating_end_point = true;
    }

    if(ImGui::Button("Calculate Shortest Point")) {
        if(const std::vector<MapPoint*> result = DijkstraAlgorithm::findShortestPath(); !result.empty()) {
            std::cout << "Shortest Path Length: " << result.size() << std::endl;
            for(MapPoint* mapPoint : result) {
                mapPoint->setAsPath();
            }
        }
    }

}


