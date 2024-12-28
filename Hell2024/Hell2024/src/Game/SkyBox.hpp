#pragma once

#include <glm/glm.hpp>

struct SkyBox
{
    inline static bool SKYBOX_ENABLED = true;
    inline static glm::vec3 SKYBOX_TINT = glm::vec3(2.5);

    struct Plane
    {
        inline static constexpr float VERY_NEAR_DISTANCE = 0.0005f;
        inline static constexpr float NEAR_DISTANCE = 0.0025f;
        inline static constexpr float FAR_DISTANCE = 200.0f;
        inline static constexpr float VERY_FAR_DISTANCE = 500.0f;
        inline static constexpr float EXTREMELY_FAR_DISTANCE = 900.0f;
    };
};

