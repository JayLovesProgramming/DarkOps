#pragma once

#include "HellCommon.hpp"
#include "../Physics/Physics.hpp"

struct BulletCasing 
{
    PxShape* m_pxShape = NULL;
    PxRigidBody* m_pxRigidBody = NULL;
    float m_audioDelay = 0.0f;
    float m_lifeTime = 0.0f;
    glm::mat4 m_modelMatrix = glm::mat4(1);
    bool m_collisionsEnabled = false;

    int m_modelIndex = 0;
    int m_materialIndex = 0;

    void Update(float deltaTime);
    void CollisionResponse();
    void CleanUp();

    glm::mat4 GetModelMatrix();
};
