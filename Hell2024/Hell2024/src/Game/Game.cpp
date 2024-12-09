﻿#include "Game.hpp"
#include "Scene.hpp"
#include "BackEnd/BackEnd.hpp"
#include "Core/Audio.hpp"
#include "Editor/CSG.hpp"
#include "Editor/Editor.hpp"
#include "Input/Input.hpp"
#include "Input/InputMulti.hpp"
#include "Renderer/GlobalIllumination.hpp"
#include "Renderer/Renderer.hpp"
#include "Pathfinding/Pathfinding2.hpp"
#include "RapidHotload.hpp"

namespace Game
{
    GameMode _gameMode = {};
    MultiplayerMode _multiplayerMode = {};
    SplitscreenMode _splitscreenMode = {};
    GameSettings g_gameSettings;
    bool _isLoaded = false;
    double _deltaTimeAccumulator = 0.0;
    double _fixedDeltaTime = 1.0 / 60.0;
    std::vector<Player> g_players;
    bool _showDebugText = true;

    bool g_firstFrame = true;
    double g_lastFrame = 0;
    double g_thisFrame = 0;
    bool g_takeDamageOutside = false;
    float g_time = 0;

    void EvaluateDebugKeyPresses();

    void Create() 
    {
        _gameMode = GameMode::GAME;
        _multiplayerMode = MultiplayerMode::LOCAL;
        _splitscreenMode = SplitscreenMode::NONE;
        _isLoaded = true;
        g_firstFrame = true;

        GlobalIllumination::RecalculateGI();

        CreatePlayers(3);

        Scene::Init();
        //Audio::PlayAudio("INTRO_EVIL_LAUGH_02.wav", 0.6f);

  /*      Model* model = AssetManager::GetModelByName("SPAS_Isolated");
        for (auto& idx : model->GetMeshIndices())
        {
            Mesh* mesh = AssetManager::GetMeshByIndex(idx);
            std:cout << mesh->name << "\n";
        }*/
        
        std::cout << "\n";

        WeaponManager::PreLoadWeaponPickUpConvexHulls();

        g_gameSettings.takeDamageOutside = true;
        g_gameSettings.skyBoxTint = glm::vec3(0.3, 0.15, 0.03);

        g_gameSettings.takeDamageOutside = false;
        g_gameSettings.skyBoxTint = glm::vec3(1);

        // std::cout << "Game::Create() succeeded\n";
        // Edgecase bug - we crash after game has created
    }

    bool IsLoaded() 
    {
        return _isLoaded;
    }

    void Update() 
    {
        if (g_firstFrame)
        {
            g_thisFrame = glfwGetTime();
            g_firstFrame = false;
        }

        RapidHotload::Update();

        // Delta Time
        g_lastFrame = g_thisFrame;
        g_thisFrame = glfwGetTime();

        deltaTime = g_thisFrame - g_lastFrame;
        _deltaTimeAccumulator += deltaTime;
        g_time += deltaTime;

        // Constructive Solid Geometry (CSG)
        if (Input::KeyPressed(GLFW_KEY_O)) 
        {
            Physics::ClearCollisionLists();
            Scene::LoadDefaultScene();
            Audio::PlayAudio(AUDIO_SELECT, 1.00f);
        }
        CSG::Update();
        Pathfinding2::Update(deltaTime);

        // Editor
        if (Input::KeyPressed(HELL_KEY_F1) || Input::KeyPressed(HELL_KEY_F2) || Input::KeyPressed(HELL_KEY_F3)) 
        {
            Audio::PlayAudio(AUDIO_SELECT, 1.00f);
            Editor::EnterEditor();
        }

        if (Input::KeyPressed(HELL_KEY_TAB)) 
        {
            Audio::PlayAudio(AUDIO_SELECT, 1.00f);
            if (Editor::IsOpen()) 
            {
                Editor::LeaveEditor();
            }
            else 
            {
                Editor::EnterEditor();
            }
        }

        if (Editor::IsOpen()) 
        {
            Editor::Update(deltaTime);
        }

        // Physics
        while (_deltaTimeAccumulator >= _fixedDeltaTime) 
        {
            _deltaTimeAccumulator -= _fixedDeltaTime;
            Physics::StepPhysics(_fixedDeltaTime);
        }

        // Debug key presses
        EvaluateDebugKeyPresses();

        // Player update
        InputMulti::Update();

        for (Player& player : g_players)
        {
            player.UpdatePlayer1(deltaTime);
        }

        InputMulti::ResetMouseOffsets();
        Scene::Update(deltaTime);

        if (g_dogDeaths == -1)
        {
            std::ifstream file("DogDeaths.txt");
            std::stringstream buffer;
            buffer << file.rdbuf();
            g_dogDeaths = std::stoi(buffer.str());
        }

        if (g_playerDeaths == -1)
        {
            std::ifstream file("PlayerDeaths.txt");
            std::stringstream buffer;
            buffer << file.rdbuf();
            g_playerDeaths = std::stoi(buffer.str());
        }

        // Populate Player Data
        for (int i = 0; i < g_players.size(); i++)
        {
            g_playerData[i].flashlightOn = g_players[i].m_flashlightOn;
        }
    }

    void CreatePlayers(unsigned int playerCount)
    {
        g_players.clear();
        g_playerData.resize(4);

        for (int i = 0; i < playerCount; i++)
        {
            Game::g_players.push_back(Player(i));
        }

        SetPlayerKeyboardAndMouseIndex(0, 0, 0);
        SetPlayerKeyboardAndMouseIndex(1, 1, 1);
        SetPlayerKeyboardAndMouseIndex(2, 1, 1);
        SetPlayerKeyboardAndMouseIndex(3, 1, 1);

        PxU32 p1RagdollCollisionGroupFlags = RaycastGroup::PLAYER_1_RAGDOLL;
        PxU32 p2RagdollCollisionGroupFlags = RaycastGroup::PLAYER_2_RAGDOLL;
        PxU32 p3RagdollCollisionGroupFlags = RaycastGroup::PLAYER_3_RAGDOLL;
        PxU32 p4RagdollCollisionGroupFlags = RaycastGroup::PLAYER_4_RAGDOLL;

        AnimatedGameObject* p1characterModel = Scene::GetAnimatedGameObjectByIndex(Game::g_players[0].GetCharacterModelAnimatedGameObjectIndex(), "p1characterModel");
        AnimatedGameObject* p2characterModel = Scene::GetAnimatedGameObjectByIndex(Game::g_players[1].GetCharacterModelAnimatedGameObjectIndex(), "p2characterModel");
        AnimatedGameObject* p3characterModel = Scene::GetAnimatedGameObjectByIndex(Game::g_players[2].GetCharacterModelAnimatedGameObjectIndex(), "p3characterModel");
        AnimatedGameObject* p4characterModel = Scene::GetAnimatedGameObjectByIndex(Game::g_players[3].GetCharacterModelAnimatedGameObjectIndex(), "p4characterModel");

        p1characterModel->LoadRagdoll("UnisexGuy3.rag", p1RagdollCollisionGroupFlags);
        p2characterModel->LoadRagdoll("UnisexGuy3.rag", p2RagdollCollisionGroupFlags);

        Game::g_players[0]._interactFlags = RaycastGroup::RAYCAST_ENABLED;
        Game::g_players[1]._interactFlags = RaycastGroup::RAYCAST_ENABLED;

        Game::g_players[0]._interactFlags &= ~RaycastGroup::PLAYER_1_RAGDOLL;
        Game::g_players[1]._interactFlags &= ~RaycastGroup::PLAYER_2_RAGDOLL;

        Game::g_players[0]._bulletFlags = RaycastGroup::RAYCAST_ENABLED | RaycastGroup::PLAYER_2_RAGDOLL | RaycastGroup::PLAYER_3_RAGDOLL | RaycastGroup::PLAYER_4_RAGDOLL | RaycastGroup::DOBERMAN;
        Game::g_players[1]._bulletFlags = RaycastGroup::RAYCAST_ENABLED | RaycastGroup::PLAYER_1_RAGDOLL | RaycastGroup::PLAYER_3_RAGDOLL | RaycastGroup::PLAYER_4_RAGDOLL | RaycastGroup::DOBERMAN;
        
        Game::g_players[0]._playerName = "Orion";
        Game::g_players[1]._playerName = "CrustyAssCracker";

        if (g_players.size() == 4)
        {
            p3characterModel->LoadRagdoll("UnisexGuy3.rag", p3RagdollCollisionGroupFlags);
            p4characterModel->LoadRagdoll("UnisexGuy3.rag", p4RagdollCollisionGroupFlags);
            Game::g_players[2]._interactFlags = RaycastGroup::RAYCAST_ENABLED;
            Game::g_players[2]._interactFlags &= ~RaycastGroup::PLAYER_3_RAGDOLL;
            Game::g_players[3]._interactFlags = RaycastGroup::RAYCAST_ENABLED;
            Game::g_players[3]._interactFlags &= ~RaycastGroup::PLAYER_4_RAGDOLL;
            Game::g_players[2]._bulletFlags = RaycastGroup::RAYCAST_ENABLED | RaycastGroup::PLAYER_1_RAGDOLL | RaycastGroup::PLAYER_2_RAGDOLL | RaycastGroup::PLAYER_4_RAGDOLL | RaycastGroup::DOBERMAN;
            Game::g_players[3]._bulletFlags = RaycastGroup::RAYCAST_ENABLED | RaycastGroup::PLAYER_1_RAGDOLL | RaycastGroup::PLAYER_2_RAGDOLL | RaycastGroup::PLAYER_3_RAGDOLL | RaycastGroup::DOBERMAN;
            Game::g_players[2]._playerName = "P3";
            Game::g_players[3]._playerName = "P4";
        }

        for (RigidComponent& rigid : p1characterModel->_ragdoll._rigidComponents)
        {
            PxShape* shape;
            rigid.pxRigidBody->getShapes(&shape, 1);
            shape->setFlag(PxShapeFlag::eVISUALIZATION, false);
        }

        std::cout << "[INFO] Created " << g_players.size() << " Players" << std::endl;
    }

    std::string Game::GetPlayerNameByIndex(int index)
    {
        return g_players[index]._playerName;
    }

    //int Game::GetPlayerIndexByName(std::string name)
    //{
    //    //return g_players[]
    //}

    const int GetPlayerCount()
    {
        return g_players.size();
    }

    const GameMode& GetGameMode() 
    {
        return _gameMode;
    }

    Player* GetPlayerByIndex(unsigned int index)
    {
        if (index >= 0 && index < g_players.size())
        {
            return &g_players[index];
        }
        else 
        {
            //std::cout << "Game::GetPlayerByIndex() failed because index was out of range. Size of Game::_players is " << GetPlayerCount() << "\n";
            return nullptr;
        }
    }

    void SetPlayerKeyboardAndMouseIndex(int playerIndex, int keyboardIndex, int mouseIndex)
    {
        if (playerIndex >= 0 && playerIndex < Game::GetPlayerCount())
        {
            g_players[playerIndex].SetKeyboardIndex(keyboardIndex);
            g_players[playerIndex].SetMouseIndex(mouseIndex);
        }
    }

    void SetPlayerGroundedStates()
    {
        for (Player& player : g_players) 
        {
            player._isGrounded = false;
            for (auto& report : Physics::_characterCollisionReports)
            {
                if (report.characterController == player._characterController && report.hitNormal.y > 0.5f)
                {
                    player._isGrounded = true;
                }
            }
        }
    }

    void GiveControlToPlayer1()
    {
        SetPlayerKeyboardAndMouseIndex(0, 0, 0);
        SetPlayerKeyboardAndMouseIndex(1, 1, 1);
        SetPlayerKeyboardAndMouseIndex(2, 1, 1);
        SetPlayerKeyboardAndMouseIndex(3, 1, 1);

        for (Player& player : g_players)
        {
            g_players[0].DisableControl();
        }

        g_players[0].EnableControl();
    }

    const int GetPlayerIndexFromPlayerPointer(Player* player) 
    {
        for (int i = 0; i < g_players.size(); i++) 
        {
            if (&g_players[i] == player)
            {
                return i;
            }
        }
        return -1;
    }

    const MultiplayerMode& GetMultiplayerMode() 
    {
        return _multiplayerMode;
    }

    const SplitscreenMode& GetSplitscreenMode() 
    {
        return _splitscreenMode;
    }

    void NextSplitScreenMode()
    {
        int currentSplitScreenMode = (int)(_splitscreenMode);
        currentSplitScreenMode++;
        if (currentSplitScreenMode == (int)(SplitscreenMode::SPLITSCREEN_MODE_COUNT))
        {
            currentSplitScreenMode = 0;
        }
        _splitscreenMode = (SplitscreenMode)currentSplitScreenMode;
    }

    void SetSplitscreenMode(SplitscreenMode mode)
    {
        _splitscreenMode = mode;
    }

    void PrintPlayerControlIndices()
    {
        std::cout << "\n";
        for (int i = 0; i < g_players.size(); i++)
        {
            std::cout << "Player " << i << ": keyboard[";
            std::cout << g_players[i].GetKeyboardIndex() << "] mouse[";
            std::cout << g_players[i].GetMouseIndex() << "]\n";
        }
    }

    static void RespawnAllPlayers()
    {
        for (Player& player : g_players) 
        {
            player.Respawn();
        }
    }

    static void RespawnAllDeadPlayers()
    {
        for (Player& player : g_players)
        {
            if (player.IsDead()) {
                player.Respawn();
            }
        }
    }

    static void SetPlayerControls(int keyPressed)
    {
        switch (keyPressed) 
        {
        case 1: // HELL_KEY_1
            SetPlayerKeyboardAndMouseIndex(0, 0, 0); // SAME 1(keyboard) 1(mouse)
            SetPlayerKeyboardAndMouseIndex(1, 1, 1); // SAME 0(keyboard) 0(mouse)
            SetPlayerKeyboardAndMouseIndex(2, 1, 1); // SAME
            SetPlayerKeyboardAndMouseIndex(3, 1, 1); // SAME
            break;
        case 2: // HELL_KEY_2
            SetPlayerKeyboardAndMouseIndex(0, 1, 1);
            SetPlayerKeyboardAndMouseIndex(1, 0, 0);
            SetPlayerKeyboardAndMouseIndex(2, 1, 1);
            SetPlayerKeyboardAndMouseIndex(3, 1, 1);
            break;
        case 3: // HELL_KEY_3
            SetPlayerKeyboardAndMouseIndex(0, 1, 1);
            SetPlayerKeyboardAndMouseIndex(1, 1, 1);
            SetPlayerKeyboardAndMouseIndex(2, 0, 0);
            SetPlayerKeyboardAndMouseIndex(3, 1, 1);
            break;
        case 4: // HELL_KEY_4
            SetPlayerKeyboardAndMouseIndex(0, 1, 1);
            SetPlayerKeyboardAndMouseIndex(1, 1, 1);
            SetPlayerKeyboardAndMouseIndex(2, 1, 1);
            SetPlayerKeyboardAndMouseIndex(3, 0, 0);
            break;
        default:
            break;
        }
    }

    static void CheckInputAndSetPlayerControls() 
    {
        if (Input::KeyPressed(HELL_KEY_1)) 
        {
            SetPlayerControls(1);
        }
        else if (Input::KeyPressed(HELL_KEY_2))
        {
            SetPlayerControls(2);
        }
        else if (Input::KeyPressed(HELL_KEY_3))
        {
            SetPlayerControls(3);
        }
        else if (Input::KeyPressed(HELL_KEY_4))
        {
            SetPlayerControls(4);
        }
    }


    void EvaluateDebugKeyPresses() 
    {
        if (Input::KeyPressed(HELL_KEY_B))
        {
            Audio::PlayAudio(AUDIO_SELECT, 1.00f);
            Renderer::NextDebugLineRenderMode();
        }
        if (Input::KeyPressed(HELL_KEY_X))
        {
            Audio::PlayAudio(AUDIO_SELECT, 1.00f);
            Renderer::PreviousRenderMode();
        }
        if (Input::KeyPressed(HELL_KEY_Z)) 
        {
            Audio::PlayAudio(AUDIO_SELECT, 1.00f);
            Renderer::NextRenderMode();
        }
        if (Input::KeyPressed(GLFW_KEY_Y))
        {
            Audio::PlayAudio(AUDIO_SELECT, 1.00f);
            Renderer::ToggleProbes();
        }

        if (!Editor::IsOpen()) 
        {
            CheckInputAndSetPlayerControls();
        }

        if (Input::KeyPressed(HELL_KEY_J)) 
        {
            RespawnAllDeadPlayers();
        }

        if (Input::KeyPressed(HELL_KEY_K)) 
        {
            if (Editor::IsOpen()) 
            {
                std::cout << "Pos:" << Util::Vec3ToString(Game::GetPlayerByIndex(0)->GetFeetPosition()) << "\n";
                std::cout << "Rot:" << Util::Vec3ToString(Game::GetPlayerByIndex(0)->GetViewRotation()) << "\n";
            }
            else 
            {
                RespawnAllPlayers();
            }
        }

        if (Input::KeyPressed(HELL_KEY_GRAVE_ACCENT))
        {
            _showDebugText = !_showDebugText;
            Audio::PlayAudio(AUDIO_SELECT, 1.00f);
        }
    }

    const bool DebugTextIsEnabled()
    {
        return _showDebugText;
    }

    // Pickups
    void SpawnAmmo(std::string type, glm::vec3 position, glm::vec3 rotation, bool wakeOnStart)
    {
        AmmoInfo* ammoInfo = WeaponManager::GetAmmoInfoByName(type);

        if (ammoInfo)
        {
            Scene::CreateGameObject();
            GameObject* pickup = Scene::GetGameObjectByIndex(Scene::GetGameObjectCount() - 1);
            pickup->SetPosition(position);
            pickup->SetRotation(rotation);
            pickup->SetModelMatrixMode(ModelMatrixMode::PHYSX_TRANSFORM);
            pickup->PutRigidBodyToSleep();
            pickup->SetCollisionType(CollisionType::PICKUP);
            pickup->SetKinematic(false);
            pickup->SetWakeOnStart(wakeOnStart);
            pickup->SetModel(ammoInfo->modelName);
            pickup->SetName(type);
            pickup->SetMeshMaterial(ammoInfo->materialName);
            pickup->SetPickUpType(PickUpType::AMMO);
            pickup->AddCollisionShapeFromModelIndex(AssetManager::GetModelIndexByName(ammoInfo->convexMeshModelName));
            pickup->SetRaycastShapeFromModelIndex(AssetManager::GetModelIndexByName(ammoInfo->convexMeshModelName));
            pickup->UpdateRigidBodyMassAndInertia(150.0f);
        }
    }

    void SpawnPickup(PickUpType pickupType, glm::vec3 position, glm::vec3 rotation, bool wakeOnStart)
    {
        if (pickupType == PickUpType::NONE)
        {
            return;
        }

        Scene::CreateGameObject();
        GameObject* pickup = Scene::GetGameObjectByIndex(Scene::GetGameObjectCount() - 1);
        pickup->SetPosition(position);
        pickup->SetRotation(rotation);
        pickup->SetModelMatrixMode(ModelMatrixMode::PHYSX_TRANSFORM);
        pickup->PutRigidBodyToSleep();
        pickup->SetCollisionType(CollisionType::PICKUP);
        pickup->SetKinematic(false);
        pickup->SetWakeOnStart(wakeOnStart);

        if (pickupType == PickUpType::GLOCK_AMMO)
        {
            pickup->SetModel("GlockAmmoBox");
            pickup->SetName("GlockAmmo_PickUp");
            pickup->SetMeshMaterial("GlockAmmoBox");
            pickup->SetPickUpType(PickUpType::GLOCK_AMMO);
            pickup->AddCollisionShapeFromModelIndex(AssetManager::GetModelIndexByName("GlockAmmoBox_ConvexMesh"));
            pickup->SetRaycastShapeFromModelIndex(AssetManager::GetModelIndexByName("GlockAmmoBox_ConvexMesh"));
            pickup->UpdateRigidBodyMassAndInertia(150.0f);
        }

        if (pickupType == PickUpType::TOKAREV_AMMO)
        {
            pickup->SetModel("TokarevAmmoBox");
            pickup->SetName("GlockAmmo_PickUp");
            pickup->SetMeshMaterial("TokarevAmmoBox");
            pickup->SetPickUpType(PickUpType::GLOCK_AMMO);
            pickup->AddCollisionShapeFromModelIndex(AssetManager::GetModelIndexByName("TokarevAmmoBox_ConvexMesh"));
            pickup->SetRaycastShapeFromModelIndex(AssetManager::GetModelIndexByName("TokarevAmmoBox_ConvexMesh"));
            pickup->UpdateRigidBodyMassAndInertia(150.0f);
        }
    }

    float GetTime()
    {
        return g_time;
    }

    const GameSettings& GetSettings()
    {
        return g_gameSettings;
    }
}
