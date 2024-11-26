#pragma once

#include "HellCommon.h"

struct PickUp
{
    enum class Type { GLOCK_AMMO = 0 };

    Type type;
    glm::vec3 position;
    glm::vec3 rotation;
    std::string parentGameObjectName = "";
    bool pickedUp = false;
    float timeSincePickedUp = 0.0f;
    float respawnTime = 10.0f;

    glm::mat4 GetModelMatrix()
    {
        Transform transform;
        transform.position = position;
        transform.rotation = rotation;
        return transform.to_mat4();
    }

    void Update(float deltaTime)
    {
        if (pickedUp)
        {
            timeSincePickedUp += deltaTime;
        }
        if (timeSincePickedUp > respawnTime)
        {
            pickedUp = false;
            timeSincePickedUp = 0;
        }
    }
};