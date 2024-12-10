#pragma once

#include "Scene.hpp"
#include "Sofa.hpp"

using Scene::CreateGameObject, Scene::GetGameObjectByIndex, Scene::GetGameObjectCount;

class CushionManager
{
public:
    constexpr static float cushionDensity = 20.0f;

	void inline static CreateAllCushions()
	{
        CreateGameObject();
        GameObject* cushion0 = GetGameObjectByIndex(GetGameObjectCount() - 1);
        cushion0->SetPosition(SofaManager::sofaX, 0.4f, 1.89f);
        cushion0->SetRotationY(HELL_PI * -0.5f);
        cushion0->SetModel("SofaCushion0");
        cushion0->SetMeshMaterial("Sofa");
        cushion0->SetName("SofaCushion0");
        cushion0->SetKinematic(false);
        cushion0->SetRaycastShapeFromModelIndex(AssetManager::GetModelIndexByName("SofaCushion0"));
        cushion0->AddCollisionShapeFromModelIndex(AssetManager::GetModelIndexByName("SofaCushion0_ConvexMesh"));
        cushion0->SetModelMatrixMode(ModelMatrixMode::PHYSX_TRANSFORM);
        cushion0->UpdateRigidBodyMassAndInertia(cushionDensity);
        cushion0->SetCollisionType(CollisionType::BOUNCEABLE);

        CreateGameObject();
        GameObject* cushion1 = GetGameObjectByIndex(GetGameObjectCount() - 1);
        cushion1->SetPosition(SofaManager::sofaX, 0.4f, 1.89f);
        cushion1->SetModel("SofaCushion1");
        cushion1->SetName("SofaCushion1");
        cushion1->SetMeshMaterial("Sofa");
        cushion1->SetKinematic(false);
        cushion1->SetRaycastShapeFromModelIndex(AssetManager::GetModelIndexByName("SofaCushion0"));
        cushion1->AddCollisionShapeFromModelIndex(AssetManager::GetModelIndexByName("SofaCushion1_ConvexMesh"));
        cushion1->SetModelMatrixMode(ModelMatrixMode::PHYSX_TRANSFORM);
        cushion1->UpdateRigidBodyMassAndInertia(cushionDensity);
        cushion1->SetCollisionType(CollisionType::BOUNCEABLE);
        cushion1->SetRotationY(HELL_PI * -0.5f);

        CreateGameObject();
        GameObject* cushion2 = GetGameObjectByIndex(GetGameObjectCount() - 1);
        cushion2->SetPosition(SofaManager::sofaX, 0.4f, 1.89f);
        cushion2->SetModel("SofaCushion2");
        cushion2->SetName("SofaCushion2");
        cushion2->SetMeshMaterial("Sofa");
        cushion2->SetKinematic(false);
        cushion2->SetRaycastShapeFromModelIndex(AssetManager::GetModelIndexByName("SofaCushion2"));
        cushion2->AddCollisionShapeFromModelIndex(AssetManager::GetModelIndexByName("SofaCushion2_ConvexMesh"));
        cushion2->SetModelMatrixMode(ModelMatrixMode::PHYSX_TRANSFORM);
        cushion2->UpdateRigidBodyMassAndInertia(cushionDensity);
        cushion2->SetCollisionType(CollisionType::BOUNCEABLE);
        cushion2->SetRotationY(HELL_PI * -0.5f);

        CreateGameObject();
        GameObject* cushion3 = GetGameObjectByIndex(GetGameObjectCount() - 1);
        cushion3->SetPosition(SofaManager::sofaX, 0.4f, 1.89f);
        cushion3->SetModel("SofaCushion3");
        cushion3->SetName("SofaCushion3");
        cushion3->SetMeshMaterial("Sofa");
        cushion3->SetKinematic(false);
        cushion3->SetRaycastShapeFromModelIndex(AssetManager::GetModelIndexByName("SofaCushion3"));
        cushion3->AddCollisionShapeFromModelIndex(AssetManager::GetModelIndexByName("SofaCushion3_ConvexMesh"));
        cushion3->SetModelMatrixMode(ModelMatrixMode::PHYSX_TRANSFORM);
        cushion3->UpdateRigidBodyMassAndInertia(cushionDensity);
        cushion3->SetCollisionType(CollisionType::BOUNCEABLE);
        cushion3->SetRotationY(HELL_PI * -0.5f);

        CreateGameObject();
        GameObject* cushion4 = GetGameObjectByIndex(GetGameObjectCount() - 1);
        cushion4->SetPosition(SofaManager::sofaX, 0.4f, 1.89f);
        cushion4->SetModel("SofaCushion4");
        cushion4->SetName("SofaCushion4");
        cushion4->SetMeshMaterial("Sofa");
        cushion4->SetKinematic(false);
        cushion4->SetRaycastShapeFromModelIndex(AssetManager::GetModelIndexByName("SofaCushion4"));
        cushion4->AddCollisionShapeFromModelIndex(AssetManager::GetModelIndexByName("SofaCushion4_ConvexMesh"));
        cushion4->SetModelMatrixMode(ModelMatrixMode::PHYSX_TRANSFORM);
        cushion4->UpdateRigidBodyMassAndInertia(15.0f);
        cushion4->SetCollisionType(CollisionType::BOUNCEABLE);
        cushion4->SetRotationY(HELL_PI * -0.5f);
	}
};