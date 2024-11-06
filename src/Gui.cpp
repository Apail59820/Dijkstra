//
// Created by Amaury Paillard on 05/11/2024.
//

#include "../include/Gui.h"
#include <imgui-SFML.h>
#include <imgui.h>

#include "../include/DijkstraAlgorithm.h"
#include "../include/MapPoint.h"
#include "../include/Globals.h"
#include "../include/SaveManager.h"

Gui::Gui() = default;

Gui::~Gui() = default;


void Gui::Render() {

    ImGui::InputText("Name", reinterpret_cast<char *>(&Globals::mapPointNameInput), 12,
                     Globals::is_adding_point ? ImGuiInputTextFlags_ReadOnly : ImGuiInputTextFlags_AutoSelectAll);
    ImGui::SameLine();
    ImGui::Checkbox("Auto name", &Globals::auto_name);

    if (ImGui::Button("Add Point")) {
        Globals::is_creating_end_point = false;
        Globals::is_creating_start_point = false;

        if(Globals::is_creating_route && Globals::route_point_a != nullptr) {
            Globals::route_manager->CancelRouteCreation();
            Globals::is_creating_route = false;
        }

        Globals::notification_manager->addNotification("Mode: \"Add point\"");
        Globals::is_adding_point = true;
    }

    if (ImGui::Button("Create Route")) {
        Globals::is_creating_route = true;
        Globals::is_creating_end_point = false;
        Globals::is_creating_start_point = false;
        Globals::is_adding_point = false;

        Globals::notification_manager->addNotification("Mode: \"Create route\"");
    }

    ImGui::SliderFloat("Friction Coefficient", &Globals::friction_coefficient, 0.0f, 1.0f);
    ImGui::SliderInt("Physics Sub Steps", &Globals::physic_sub_steps, 1, 50);
    ImGui::Text("Routes : %i", Globals::route_amount);
    ImGui::Checkbox("Show Distances", &Globals::show_distances);

    if (ImGui::Button("Set Start Point")) {
        Globals::is_creating_route = false;
        Globals::is_creating_end_point = false;
        Globals::is_creating_start_point = true;
        Globals::is_adding_point = false;

        Globals::notification_manager->addNotification("Mode: \"Set start point\"");
    }

    ImGui::SameLine();

    if (ImGui::Button("Set End Point")) {
        Globals::is_creating_route = false;
        Globals::is_creating_start_point = false;
        Globals::is_creating_end_point = true;

        Globals::notification_manager->addNotification("Mode: \"Set end point\"");
    }

    if (ImGui::Button("Calculate Shortest Point")) {
        if (const std::vector<MapPoint *> result = DijkstraAlgorithm::findShortestPath(); !result.empty()) {
            for (MapPoint *mapPoint: result) {
                mapPoint->setAsPath();
            }
        }
    }

    if(ImGui::Button("Save Graph")) {
        SaveManager::SaveToFile();
    }

    ImGui::SameLine();

    if (ImGui::Button("Load Graph")) {
        SaveManager::LoadFromFile();
    }
}
