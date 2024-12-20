#include "AssetBrowser.hpp"

#include "Input/Input.hpp"
#include "Renderer/ImGui/F8Console.hpp"

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
        //IMGUI::AddToConsoleLog("Asset Browser: Spawned Speed Cola (PERK)");
    }
    else if (filePath == "Juggernog")
    {
        SpawnAssetBrowserModel("Juggernog", { -0.1f, -0.2f, 3.8f }, 0.021f);
        //IMGUI::AddToConsoleLog("Asset Browser: Spawned Juggernog (PERK)");
    }


    else if (filePath == "Cube")
    {
        Editor::PutDownCSGAdditive();
    }
}

void AssetBrowser::RenderMainDockspace()
{
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    ImGui::Begin("DockSpace", nullptr, window_flags);
    ImGui::PopStyleVar(2);

    ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

    ImGui::End();
}

void AssetBrowser::HandleToggleAssetBrowser()
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
}

void AssetBrowser::HandleDragDrop()
{
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

void AssetBrowser::Render()
{
    HandleToggleAssetBrowser();

    if (!ASSET_BROWSER_OPEN)
    {
        return;
    }

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(viewport->Size, ImGuiCond_Always);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::Begin("Main Window", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);

    // DockSpace
    ImGuiID dockspace_id = ImGui::GetID("MainDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0, 0), ImGuiDockNodeFlags_None);

    if (ImGui::BeginMenuBar()) 
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit")) 
            {
                // Handle exit logic here
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) 
        {
            ImGui::MenuItem("Settings");
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    // Scene Panel (LEFT)
    ImGui::Begin("Scene Panel");
        // Scene Hierachy
        ImGui::Text("Scene");
        ImGui::InputText("Search", searchBuffer, sizeof(searchBuffer));
        ImGui::Separator();
        ImGui::Text("Scene Object 1");
        ImGui::Text("Scene Object 2");
    ImGui::End();

    // Viewport/Game Panel (CENTERED)
    ImGui::Begin("Viewport");
        ImGui::Text("Viewport area");
        ImGui::Separator();
        ImGui::TextWrapped("This is where your main scene content will be displayed");
    ImGui::End();

    // Content Browser Panel (BOTTOM)
    ImGui::Begin("Content Broswer");
        ImGui::Text("A column here plz.");
        ImGui::Separator();
        ImGui::TextWrapped("This is the bottom panel, used for the content browser");
    ImGui::End();

    //HandleDragDrop();

    ImGui::End();
}