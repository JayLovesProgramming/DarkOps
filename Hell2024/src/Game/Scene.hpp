#pragma once

#include "HellCommon.hpp"
#include "GameObject.hpp"
#include "AnimatedGameObject.hpp"
#include "Light.hpp"
#include "Core/CreateInfo.hpp"
#include "Physics/Physics.hpp"
#include "Editor/CSGShape.hpp"
#include "Effects/BloodDecal.hpp"
#include "Effects/BulletCasing.hpp"
#include "Effects/BulletHoleDecal.hpp"
#include "Core/VolumetricBloodSplatter.hpp"
#include "Editor/CSG.hpp"
#include "Game/Player.hpp"
#include "Game/Dobermann.hpp"
#include "Renderer/Types/HeightMap.hpp"
#include "Types/Modular/Door.hpp"
#include "Types/Modular/Staircase.hpp"
#include "Types/Modular/Toilet.hpp"
#include "Types/Modular/Window.hpp"
#include "Utils/Util.hpp"

#include "Editor/CSGPlane.hpp"
#include <string>
#include "Utils/Normal/Normal_OpenGL.hpp"
#include "Pickup.hpp"
#include "Bullet.hpp"
#include "SpawnPoint.hpp"
#include "RTMesh.hpp"
#include "RTInstance.hpp"

constexpr static auto PROPOGATION_SPACING = 1;
#define PROPOGATION_WIDTH (MAP_WIDTH / PROPOGATION_SPACING)
#define PROPOGATION_HEIGHT (MAP_HEIGHT / PROPOGATION_SPACING)
#define PROPOGATION_DEPTH (MAP_DEPTH / PROPOGATION_SPACING)

namespace Scene
{
    inline bool g_needToPlantTrees = true;
    void Update(float deltaTime);
    void SaveMapData(const std::string& fileName);
    void RemoveGameObjectByIndex(int index);

    void LoadEmptyScene();
    void LoadDefaultScene();
    void CreateBottomLevelAccelerationStructures();
    void CreateTopLevelAccelerationStructures();
    void RecreateFloorTrims();
    void RecreateCeilingTrims();

    // Bullet Hole Decals
    void CreateBulletDecal(glm::vec3 localPosition, glm::vec3 localNormal, PxRigidBody* parent, BulletHoleDecalType type);
    BulletHoleDecal* GetBulletHoleDecalByIndex(int32_t index);
    const size_t GetBulletHoleDecalCount();
    void CleanUpBulletHoleDecals();

    // Bullet Casings
    void CleanUpBulletCasings();

    // Game Objects

    int32_t CreateGameObject();
    GameObject* GetGameObjectByIndex(int32_t index);
    GameObject* GetGameObjectByName(std::string name);
    std::vector<GameObject>& GetGamesObjects();
    void UpdateGameObjects(float deltaTime);
    const size_t GetGameObjectCount();

    // Animated Game Objects
    int32_t CreateAnimatedGameObject();
    AnimatedGameObject* GetAnimatedGameObjectByIndex(int32_t index, std::string type);
    std::vector<AnimatedGameObject>& GetAnimatedGamesObjects();
    std::vector<AnimatedGameObject*> GetAnimatedGamesObjectsToSkin();
    //void UpdateAnimatedGameObjects(float deltaTime);
    const size_t GetAnimatedGameObjectCount();

    // Map stuff
    CSGPlane* GetWallPlaneByIndex(int32_t index);
    CSGPlane* GetFloorPlaneByIndex(int32_t index);
    CSGPlane* GetCeilingPlaneByIndex(int32_t index);
    CSGCube* GetCubeVolumeAdditiveByIndex(int32_t index);
    CSGCube* GetCubeVolumeSubtractiveByIndex(int32_t index);
    const size_t GetCubeVolumeAdditiveCount();

    // Cuntainers
    inline std::vector<Light> g_lights;
    inline std::vector<SpawnPoint> g_spawnPoints;
    inline std::vector<BulletCasing> g_bulletCasings;
    inline std::vector<CSGCube> g_csgAdditiveCubes;
    inline std::vector<CSGCube> g_csgSubtractiveCubes;
    inline std::vector<CSGPlane> g_csgAdditiveWallPlanes;
    inline std::vector<CSGPlane> g_csgAdditiveFloorPlanes;
    inline std::vector<CSGPlane> g_csgAdditiveCeilingPlanes;
    inline std::vector<Dobermann> g_dobermann;
    inline std::vector<Staircase> g_staircases;
    inline std::vector<BulletHoleDecal> g_bulletHoleDecals;
    inline std::vector<AABB> g_fogAABB;
    inline std::vector<BloodDecal> g_bloodDecals;
    inline std::vector<BloodDecal> g_bloodDecalsForMegaTexture;
    inline std::vector<glm::mat4> g_ceilingTrims;
    inline std::vector<glm::mat4> g_floorTrims;
    
    // Shadow map stuff
    inline std::vector<int> g_shadowMapLightIndices;
    int AssignNextFreeShadowMapIndex(int lightIndex);

    // Windows
    uint32_t GetWindowCount();
    Window* GetWindowByIndex(int index);
    std::vector<Window>& GetWindows();
    //void SetWindowPosition(uint32_t windowIndex, glm::vec3 position);
    void CreateWindow(WindowCreateInfo createInfo);

    // Doors
    uint32_t GetDoorCount();
    Door* GetDoorByIndex(int index);
    std::vector<Door>& GetDoors();
    //void SetDoorPosition(uint32_t doorIndex, glm::vec3 position);
    void CreateDoor(DoorCreateInfo createInfo);

    // Lights
    void CreateLight(LightCreateInfo createInfo);

    // CSG Objects
    void AddCSGWallPlane(CSGPlaneCreateInfo& createInfo);
    void AddCSGFloorPlane(CSGPlaneCreateInfo& createInfo);
    void AddCSGCeilingPlane(CSGPlaneCreateInfo& createInfo);

    // OLD SHIT BELOW
    inline PxTriangleMesh* _sceneTriangleMesh = NULL;
    inline PxRigidStatic* _sceneRigidDynamic = NULL;
    inline PxShape* _sceneShape = NULL;

    inline std::vector<Toilet> _toilets;
    inline std::vector<VolumetricBloodSplatter> _volumetricBloodSplatters;
    inline std::vector<PickUp> _pickUps;
    inline std::vector<Bullet> _bullets;

    inline std::vector<CloudPointOld> _cloudPoints;
    inline std::vector<glm::vec3> _rtVertices;
    inline std::vector<RTMesh> _rtMesh;
    inline std::vector<RTInstance> _rtInstances;

    // New shit
    void Init();
    std::vector<RenderItem3D> GetGeometryRenderItems();
    std::vector<RenderItem3D> CreateDecalRenderItems();

    // Old shit
	void LoadHardCodedObjects();
	void LoadMap(std::string mapPath);
	void SaveMap(std::string mapPath);
    void CleanUp();
    void Update_OLD(float deltaTime);
    void LoadLightSetup(int index);
    //AnimatedGameObject* GetAnimatedGameObjectByName(std::string);
   // std::vector<AnimatedGameObject>& GetAnimatedGameObjects();
    void CreatePointCloud();
    void CreateMeshData();
    void AddLight(Light& light);
    void AddDoor(Door& door);
    void UpdateRTInstanceData();
    void RecreateDataStructures();
    void ProcessPhysicsCollisions();
	void RecreateAllPhysicsObjects();
	void RemoveAllDecalsFromWindow(Window* window);
    void CalculateLightBoundingVolumes();
    void CheckForDirtyLights();
    void ResetGameObjectStates();
    //void DirtyAllLights();

    void CreateVolumetricBlood(glm::vec3 position, glm::vec3 rotation, glm::vec3 front);

    //Player* GetPlayerFromCharacterControler(PxController* characterController);
}