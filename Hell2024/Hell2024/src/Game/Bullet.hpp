#pragma once

#include "HellCommon.hpp"

struct Bullet
{
    glm::vec3 spawnPosition = {};
    glm::vec3 direction = {};
    Weapon type = {};
    PxU32 raycastFlags = {};
    glm::vec3 parentPlayersViewRotation = {};

    int damage = 0;
    int parentPlayerIndex = -1;
};