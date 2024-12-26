#pragma once

#include <glm/glm.hpp>

constexpr static auto TL = 0;
constexpr static auto TR = 1;
constexpr static auto BL = 2;
constexpr static auto BR = 3;

//constexpr static auto _propogationGridSpacing = 0.375f;
//constexpr static auto _maxPropogationDistance = 2.6f;

constexpr static auto inline PLAYER_COUNT = 4;
constexpr static auto inline UNDEFINED_STRING = "UNDEFINED_STRING";

struct SkyBox
{
    inline static bool SKYBOX_ENABLED = true;
    inline static glm::vec3 SKYBOX_TINT = glm::vec3(0.1);

    struct Plane
    {
        inline static constexpr float VERY_NEAR_DISTANCE = 0.0005f;
        inline static constexpr float NEAR_DISTANCE = 0.0025f;
        inline static constexpr float FAR_DISTANCE = 200.0f;
        inline static constexpr float VERY_FAR_DISTANCE = 500.0f;
        inline static constexpr float EXTREMELY_FAR_DISTANCE = 900.0f;
    };

};

// Mathematic Helpers
constexpr static auto inline DARKOPS_ROUNED_PI = 3.14159265359f;
constexpr static auto inline DARKOPS_ROUNED_HALF_PI = 1.57079632679f;
constexpr static auto inline DARKOPS_PI = 3.141592653589793f;
constexpr static auto inline DARKOPS_PHI = 1.6180f;

constexpr static auto SMALL_NUMBER = (float)9.99999993922529e-9;
constexpr static auto KINDA_SMALL_NUMBER = (float)0.00001;
constexpr static auto MIN_RAY_DIST = (float)0.01f;

#define ToRadian(x) (float)(((x) * DARKOPS_PI / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / DARKOPS_PI))

// Some functional memory stuff
#define ZERO_MEM(a) memset(a, 0, sizeof(a))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }

// Colours (vec3)
constexpr static auto inline ORANGE = glm::vec3(1, 0.647f, 0);
constexpr static auto inline BLACK = glm::vec3(0, 0, 0);
constexpr static auto inline WHITE = glm::vec3(1, 1, 1);
constexpr static auto inline RED = glm::vec3(1, 0, 0);
constexpr static auto inline GREEN = glm::vec3(0, 1, 0);
constexpr static auto inline BLUE = glm::vec3(0, 0, 1);
constexpr static auto inline YELLOW = glm::vec3(1, 1, 0);
constexpr static auto inline PURPLE = glm::vec3(1, 0, 1);
constexpr static auto inline GREY = glm::vec3(0.25f);
constexpr static auto inline LIGHT_BLUE = glm::vec3(0, 1, 1);
constexpr static auto inline LIGHT_GREEN = glm::vec3(0.16f, 0.78f, 0.23f);
constexpr static auto inline LIGHT_RED = glm::vec3(0.8f, 0.05f, 0.05f);
constexpr static auto inline GRID_COLOR = glm::vec3(0.509, 0.333, 0.490) * 0.5f;

// Normal Positions (vec3)
constexpr static auto NRM_X_FORWARD = glm::vec3(1, 0, 0);
constexpr static auto NRM_X_BACK = glm::vec3(-1, 0, 0);
constexpr static auto NRM_Y_UP = glm::vec3(0, 1, 0);
constexpr static auto NRM_Y_DOWN = glm::vec3(0, -1, 0);
constexpr static auto NRM_Z_FORWARD = glm::vec3(0, 0, 1);
constexpr static auto NRM_Z_BACK = glm::vec3(0, 0, -1);

constexpr static auto SHADOW_MAP_SIZE = 1024;
constexpr static auto SHADOW_NEAR_PLANE = 0.05f;
constexpr static auto DEFAULT_LIGHT_COLOR = glm::vec3(1, 0.7799999713897705, 0.5289999842643738);
constexpr static auto LIGHT_VOLUME_AABB_COLOR_MAP_SIZE = 256;
