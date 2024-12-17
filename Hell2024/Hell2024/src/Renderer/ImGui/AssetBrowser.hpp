#pragma once

#include <imgui.h>
#include <string>
#include <vector>
#include <filesystem>
#include <iostream>

namespace AssetBrowser
{
    inline std::string currentPath = "res/models/OBJ";
    inline std::vector<std::filesystem::directory_entry> entries;
    static bool isDragging = false; // Track whether a drag operation is active
    inline std::string draggedFilePath; // Store the path of the currently dragged file

    void updateEntries()
    {
        entries.clear();
        for (const auto& entry : std::filesystem::directory_iterator(currentPath))
        {
            entries.push_back(entry);
        }
    }


    void SpawnAssetBrowserModel(std::string name, glm::vec3 position, float scale)
    {
        Transform shapeOffset;
        shapeOffset.position.y = 0.0f;
        shapeOffset.position.z = 0.0f;

        PxShape* physics = Physics::CreateBoxShape(0.75f, 0.75f, 0.75f, shapeOffset);

        PhysicsFilterData physicsData;
        physicsData.raycastGroup = RAYCAST_DISABLED;
        physicsData.collisionGroup = CollisionGroup::ENVIROMENT_OBSTACLE;
        physicsData.collidesWith = (CollisionGroup)(GENERIC_BOUNCEABLE | BULLET_CASING | PLAYER | RAGDOLL);

        CreateGameObject();
        GameObject* assetBrowserModel = GetGameObjectByIndex(GetGameObjectCount() - 1);

        assetBrowserModel->SetPosition(position);

        assetBrowserModel->SetModel(name);
        //assetBrowserModel->SetName("PERK_SPEEDCOLA");
        assetBrowserModel->SetMeshMaterial(name.c_str());
        assetBrowserModel->SetScale(scale);
        assetBrowserModel->SetKinematic(true);

        //PERK_SPEEDCOLA->SetRaycastShapeFromModelIndex(AssetManager::GetModelIndexByName("Sofa_Cushionless"));
        assetBrowserModel->AddCollisionShape(physics, physicsData);

        //PERK_SPEEDCOLA->AddCollisionShapeFromModelIndex(AssetManager::GetModelIndexByName("SofaBack_ConvexMesh"));
        //PERK_SPEEDCOLA->AddCollisionShapeFromModelIndex(AssetManager::GetModelIndexByName("SofaLeftArm_ConvexMesh"));
        //PERK_SPEEDCOLA->AddCollisionShapeFromModelIndex(AssetManager::GetModelIndexByName("SofaRightArm_ConvexMesh"));

        assetBrowserModel->SetModelMatrixMode(ModelMatrixMode::GAME_TRANSFORM);
        assetBrowserModel->SetCollisionType(CollisionType::STATIC_ENVIROMENT);
        //PERK_SPEEDCOLA->
        //PERK_SPEEDCOLA->SetMeshMaterialByMeshName("Balls", "Gold");
    }


    void HandleDropOutsideWindow(const std::string& filePath, const ImVec2& dropPos)
    {
        // Your custom logic for handling drops outside the window
        //std::cout << "File '" << filePath << "' was dropped outside the window at position: (" << dropPos.x << ", " << dropPos.y << ")\n";
        // Example: Move the file, log it, or perform an application-specific action
        std::cout << "Dropped file: " << filePath << std::endl;

        if (filePath == "Speedcola")
        {
            SpawnAssetBrowserModel("Speedcola", { -0.1f, -0.8f, 7.8f }, 1.3f);
            IMGUI::AddToConsoleLog("Asset Browser: Spawned Speed Cola (PERK)");
        }
        else if (filePath == "Juggernog")
        {
            SpawnAssetBrowserModel("Juggernog", { -0.1f, -0.2f, 3.8f }, 0.021f);
            IMGUI::AddToConsoleLog("Asset Browser: Spawned Juggernog (PERK)");
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
                if (ImGui::Selectable(filename.c_str()))
                {
                    // Handle file selection here
                }

                if (ImGui::BeginDragDropSource())
                {
                    // Set the drag payload and mark dragging as active
                    ImGui::SetDragDropPayload("ASSET_BROWSER_ITEM", path.string().c_str(), path.string().size() + 1);
                    ImGui::Text("Dragging %s", filename.c_str());

                    isDragging = true;
                    draggedFilePath = path.string();

                    ImGui::EndDragDropSource();
                }

                if (ImGui::BeginDragDropTarget())
                {
                    if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET_BROWSER_ITEM"))
                    {
                        std::string droppedFilename = static_cast<const char*>(payload->Data);
                        std::cout << "Dropped: " << droppedFilename << std::endl;

                        // Reset dragging state
                        isDragging = false;
                    }
                    ImGui::EndDragDropTarget();
                }
            }
        }

        ImGui::End();

        // Check if drag operation ended outside the window
        if (isDragging && !ImGui::IsMouseDragging(0))
        {
            isDragging = false;
            // Mouse released outside the window
            ImVec2 mousePos = ImGui::GetMousePos();
            //std::cout << "Dropped outside window at: (" << mousePos.x << ", " << mousePos.y << ")\n";

            // Extract the filename from the path
            size_t lastSlash = draggedFilePath.find_last_of("/\\");
            std::string fileNameWithExtension = draggedFilePath.substr(lastSlash + 1);

            // Remove the file extension
            size_t lastDot = fileNameWithExtension.find_last_of('.');
            std::string fileName = fileNameWithExtension.substr(0, lastDot);


            // Perform your custom action here
            HandleDropOutsideWindow(fileName, mousePos);
        }
    }




};