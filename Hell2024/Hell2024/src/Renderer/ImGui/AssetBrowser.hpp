#pragma once

#include <imgui.h>
#include <string>
#include <vector>
#include <filesystem>
#include <iostream>

namespace AssetBrowser
{
    inline std::string currentPath = "E:/DarkOpsProjects/Hell2024/Hell2024/Hell2024/res";
    inline std::vector<std::filesystem::directory_entry> entries;

    void updateEntries()
    {
        entries.clear();
        for (const auto& entry : std::filesystem::directory_iterator(currentPath))
        {
            entries.push_back(entry);
        }
    }

    void Render()
    {
        ImGui::Begin("Asset Browser");

        if (ImGui::Button("Up"))
        {
            currentPath = std::filesystem::path(currentPath).parent_path().string();
            updateEntries();
        }

        ImGui::SameLine();
        ImGui::Text("Current Path: %s", currentPath.c_str());

        ImGui::Separator();

        for (const auto& entry : entries)
        {
            const auto& path = entry.path();
            std::string filename = path.filename().string();

            if (entry.is_directory())
            {
                if (ImGui::Selectable(filename.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick))
                {
                    if (ImGui::IsMouseDoubleClicked(0))
                    {
                        currentPath = path.string();
                        updateEntries();
                    }
                }
            }
            else
            {
                std::cout << "Rendering asset browser" << std::endl;
                if (ImGui::Selectable(filename.c_str()))
                {
                    // Handle file selection here
                }

                if (ImGui::BeginDragDropSource())
                {
                    ImGui::SetDragDropPayload("ASSET_BROWSER_ITEM", path.string().c_str(), path.string().size() + 1);
                    ImGui::Text("Dragging %s", filename.c_str());
                    ImGui::EndDragDropSource();
                }
            }
        }

        ImGui::End();
    }
}
