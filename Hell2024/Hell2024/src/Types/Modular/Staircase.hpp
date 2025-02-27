#pragma once

#include "HellCommon.hpp"
#include "Physics/Physics.hpp"

struct Staircase
{
    glm::vec3 m_position;
    float m_rotation;
    int m_stepCount = 3;

    glm::mat4 GetModelMatrix();

    void CreatePhysicsObjects();
    void CleanupPhysicsObjects();

    //std::vector<RigidStatic> m_rigidStatics;
};