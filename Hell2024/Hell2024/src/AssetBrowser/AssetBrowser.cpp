#include "AssetBrowser.hpp"

#include "Input/Input.hpp"
#include "Renderer/ImGui/GUI_UI.hpp"

bool AssetBrowser::IsAssetBrowserOpen()
{
    return ASSET_BROWSER_OPEN;
}

void AssetBrowser::UpdateEntries()
{
    entries.clear();
    for (const auto& entry : std::filesystem::directory_iterator(currentPath))
    {
        entries.push_back(entry);
    }
}

void AssetBrowser::SetSelectedAsset(GameObject* newlySelectedAsset)
{
    selectedAsset = newlySelectedAsset;
}

void AssetBrowser::RenderSidebar()
{
    ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);

    if (!selectedAsset)
    {
        ImGui::Text("No asset selected.");
        ImGui::End();
        return;
    }

     glm::vec3 position = selectedAsset->GetWorldPosition();
     glm::quat rotation = selectedAsset->GetWorldRotation();
     glm::vec3 scale = selectedAsset->GetScale();
     std::string name = selectedAsset->GetName();
    //std::cout << name << std::endl;
    if (name.c_str())
    {
        ImGui::Text(name.c_str());
        ImGui::Separator();

    }
    ImGui::Text("Transform");
    ImGui::Separator();

    if (ImGui::DragFloat3("Position", &position[0], 0.1f))
    {
        selectedAsset->SetPosition(position);
    }

    if (ImGui::DragFloat3("Rotation", &rotation[0], 0.1f))
    {
        //selectedAsset->SetRotation(rotation);
    }

    if (ImGui::DragFloat3("Scale", &scale[0], 0.1f, 0.01f, 10.0f))
    {
        selectedAsset->SetScale(scale);
    }

    ImGui::End();
}


void AssetBrowser::SpawnAssetBrowserModel(std::string name, glm::vec3 position, float scale)
{
    selectedAsset = nullptr;

    Transform shapeOffset;
    shapeOffset.position.y = 0.0f;
    shapeOffset.position.z = 0.0f;

    PxShape* physics = Physics::CreateBoxShape(0.75f, 0.75f, 0.75f, shapeOffset);

    PhysicsFilterData physicsData;
    physicsData.raycastGroup = RAYCAST_DISABLED;
    physicsData.collisionGroup = CollisionGroup::ENVIROMENT_OBSTACLE;
    physicsData.collidesWith = (CollisionGroup)(GENERIC_BOUNCEABLE | BULLET_CASING | PLAYER | RAGDOLL);

    Scene::CreateGameObject();
    GameObject* assetBrowserModel = Scene::GetGameObjectByIndex(Scene::GetGameObjectCount() - 1);
    
    assetBrowserModel->SetPosition(position);

    assetBrowserModel->SetModel(name);
    assetBrowserModel->SetName(name);
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
    selectedAsset = assetBrowserModel;
}

void AssetBrowser::HandleDropOutsideWindow(const std::string& filePath, const ImVec2& dropPos)
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


    else if (filePath == "Cube")
    {
        Editor::PutDownCSGAdditive();
    }
}

void AssetBrowser::Render()
{
    if (Input::KeyPressed(HELL_KEY_F5))
    {
        ASSET_BROWSER_OPEN = !ASSET_BROWSER_OPEN;
        if (ASSET_BROWSER_OPEN)
        {
            Input::ShowCursor();
        }
        else
        {
            Input::HideCursor();
            Input::DisableCursor();
        }
    }

    if (!ASSET_BROWSER_OPEN)
    {
        return;
    }

    RenderSidebar();

    // Bottom area for the asset browser
    ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetIO().DisplaySize.y - bottomHeight));
    //ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, bottomHeight));
    ImGui::Begin("##AssetBrowser", nullptr,
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysHorizontalScrollbar |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    // "Up" Button and Path display
    if (ImGui::Button("Up"))
    {
        currentPath = std::filesystem::path(currentPath).parent_path().string();
        UpdateEntries();
    }

    ImGui::SameLine();
    ImGui::Text("Current Path: %s", currentPath.c_str());
    ImGui::Separator();

    // Grid Layout Calculation
    float contentWidth = ImGui::GetContentRegionAvail().x;
    int columns = static_cast<int>((contentWidth + padding) / (thumbnailSize + padding));
    if (columns < 1) columns = 1;

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(padding, padding));
    ImGui::Columns(columns, nullptr, false);

    // Render each entry in the grid
    for (const auto& entry : entries)
    {
        const auto& path = entry.path();
        std::string filename = path.filename().string();

        ImGui::BeginGroup();

        if (entry.is_directory())
        {
            if (ImGui::Selectable(filename.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick, ImVec2(thumbnailSize, thumbnailSize)))
            {
                if (ImGui::IsMouseDoubleClicked(0))
                {
                    currentPath = path.string();
                    UpdateEntries();
                }
            }
        }
        else
        {
            if (ImGui::Selectable(filename.c_str(), false, 0, ImVec2(thumbnailSize, thumbnailSize)))
            {
                // Handle file selection
            }

            if (ImGui::BeginDragDropSource())
            {
                ImGui::SetDragDropPayload("ASSET_BROWSER_ITEM", path.string().c_str(), path.string().size() + 1);
                ImGui::Text("Dragging %s", filename.c_str());

                isDragging = true;
                draggedFilePath = path.string();

                ImGui::EndDragDropSource();
            }
        }

        //ImGui::TextWrapped(filename.c_str());
        ImGui::EndGroup();

        ImGui::NextColumn();
    }

    ImGui::Columns(1);
    ImGui::PopStyleVar();

    ImGui::End();

    // Handle drag-drop outside the window
    if (isDragging && !ImGui::IsMouseDragging(0))
    {
        isDragging = false;
        ImVec2 mousePos = ImGui::GetMousePos();

        size_t lastSlash = draggedFilePath.find_last_of("/\\");
        std::string fileNameWithExtension = draggedFilePath.substr(lastSlash + 1);

        size_t lastDot = fileNameWithExtension.find_last_of('.');
        std::string fileName = fileNameWithExtension.substr(0, lastDot);

        HandleDropOutsideWindow(fileName, mousePos);
    }
}