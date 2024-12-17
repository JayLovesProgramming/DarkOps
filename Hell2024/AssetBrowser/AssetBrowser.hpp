#pragma once

#include <imgui.h>
#include <imgui_internal.h>
#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include "Editor/Editor.hpp"
#include "Game/Scene.hpp"

namespace AssetBrowser
{
    inline std::string currentPath = "res/models/OBJ";
    inline std::vector<std::filesystem::directory_entry> entries;
    static bool isDragging = false; // Track whether a drag operation is active
    inline std::string draggedFilePath; // Store the path of the currently dragged file
    constexpr static float thumbnailSize = 82.0f; // Size of each grid item
    constexpr static float padding = 4.0f;       // Padding between grid items
    constexpr static float bottomHeight = 300.0f; // Height of the bottom asset browser
    static bool ASSET_BROWSER_OPEN = false;

    static inline GameObject* selectedAsset = {};
    void SetSelectedAsset(GameObject* newlySelectedAsset);

    //static inline CSGCube* selectedCSGCubeAsset = {};
    //void SetSelectedCSGCubeAsset(CSGCube* newlySelectedCSGCubeAsset);

    void UpdateEntries();
    void SpawnAssetBrowserModel(std::string name, glm::vec3 position, float scale);
    void HandleDropOutsideWindow(const std::string& filePath, const ImVec2& dropPos);
    void Render();

    void RenderSidebar();
    void RenderMainDockspace();

    bool IsAssetBrowserOpen();
};