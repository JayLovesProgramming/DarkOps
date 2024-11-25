#pragma once

#include "Scene.h"

using Scene::CreateGameObject, Scene::GetGameObjectByIndex, Scene::GetGameObjectCount;

class SofaManager
{
public:
    inline static float sofaX = 6.3f;

    inline static void CreateSofa()
	{
        float cushionHeight = 0.555f;
        Transform shapeOffset;
        shapeOffset.position.y = cushionHeight * 0.5f;
        shapeOffset.position.z = 0.5f;
        PxShape* sofaShapeBigCube = Physics::CreateBoxShape(1, cushionHeight * 0.5f, 0.4f, shapeOffset);
        PhysicsFilterData sofaFilterData;
        sofaFilterData.raycastGroup = RAYCAST_DISABLED;
        sofaFilterData.collisionGroup = CollisionGroup::ENVIROMENT_OBSTACLE;
        sofaFilterData.collidesWith = (CollisionGroup)(GENERIC_BOUNCEABLE | BULLET_CASING | PLAYER | RAGDOLL);

        CreateGameObject();
        GameObject* sofa = GetGameObjectByIndex(GetGameObjectCount() - 1);
        sofa->SetPosition(sofaX, 0.4f, 1.89f);
        sofa->SetRotationY(HELL_PI * -0.5f);
        sofa->SetName("Sofa");
        sofa->SetModel("Sofa_Cushionless");
        sofa->SetMeshMaterial("Sofa");
        sofa->SetKinematic(true);
        sofa->SetRaycastShapeFromModelIndex(AssetManager::GetModelIndexByName("Sofa_Cushionless"));
        sofa->AddCollisionShape(sofaShapeBigCube, sofaFilterData);
        sofa->AddCollisionShapeFromModelIndex(AssetManager::GetModelIndexByName("SofaBack_ConvexMesh"));
        sofa->AddCollisionShapeFromModelIndex(AssetManager::GetModelIndexByName("SofaLeftArm_ConvexMesh"));
        sofa->AddCollisionShapeFromModelIndex(AssetManager::GetModelIndexByName("SofaRightArm_ConvexMesh"));
        sofa->SetModelMatrixMode(ModelMatrixMode::GAME_TRANSFORM);
        sofa->SetCollisionType(CollisionType::STATIC_ENVIROMENT);
        //sofa->MakeGold();

        // Give the cushions some physics
        PhysicsFilterData cushionFilterData;
        cushionFilterData.raycastGroup = RAYCAST_DISABLED;
        cushionFilterData.collisionGroup = CollisionGroup::GENERIC_BOUNCEABLE;
        cushionFilterData.collidesWith = CollisionGroup(ENVIROMENT_OBSTACLE | GENERIC_BOUNCEABLE);
	}
};
