#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "Defines.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtx/hash.hpp"

struct CSGPlane 
{
    glm::vec3 m_veritces[4];
    int materialIndex = -1;

    float textureScale = 0;
    float textureOffsetX = 0;
    float textureOffsetY = 0;

    constexpr static auto CSG_PLANE_CUBE_HACKY_OFFSET = 0.1f;

    glm::vec3 GetCenter() const;

    glm::vec3 GetNormal() const;

    glm::mat4 GetModelMatrix() const;
    
    glm::mat4 GetCSGMatrix() const;
};