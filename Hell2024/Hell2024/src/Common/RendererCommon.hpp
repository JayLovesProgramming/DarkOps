#pragma once

#define GLM_FORCE_SILENT_WARNINGS
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtx/hash.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// TODO: Rename these to resoultion something
// RESOLUTION !! Oooo cool
// can increase after optimizing shizzz
constexpr static auto PRESENT_WIDTH = 1920; // 832
constexpr static auto PRESENT_HEIGHT = 1080; // 468

constexpr static auto POINT_CLOUD_SPACING = 0.4f;
//#define PROBE_SPACING 0.375f
constexpr static auto PROBE_SPACING = 0.5f;
constexpr static auto TEXTURE_ARRAY_SIZE = 1024;
constexpr static auto MAX_RENDER_OBJECTS_3D = 4096;
constexpr static auto MAX_RENDER_OBJECTS_2D = 4096;
constexpr static auto MAX_TLAS_OBJECT_COUNT = 4096;
constexpr static auto FRAME_OVERLAP = 2;
constexpr static auto MAX_LIGHTS = 300;
constexpr static auto MAX_SHADOW_CASTING_LIGHTS = 16;
constexpr static auto MAX_ANIMATED_TRANSFORMS = 2048;
constexpr static auto MAX_INSTANCES = 4096;
constexpr static auto MAX_INDIRECT_COMMANDS = 4096;
constexpr static auto MAX_GLASS_MESH_COUNT = 128;
constexpr static auto MAX_DECAL_COUNT = 4096;
constexpr static auto MAX_BLOOD_DECAL_COUNT = 1024;
constexpr static auto MAX_VAT_INSTANCE_COUNT = 16;
constexpr static auto MAX_CSG_CUBE_COUNT = 4096;
constexpr static auto MAX_SKINNED_MESH = 96;

enum Alignment 
{
    CENTERED,
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    MINIMAP_CUSTOM_TEST,
    MINIMAP_PLAYER_MARKER,
    BOTTOM_RIGHT,
    CURSOR_POS
};

struct ViewportInfo 
{
    int width = 0;
    int height = 0;
    int xOffset = 0;
    int yOffset = 0;
};

struct DrawIndexedIndirectCommand 
{
    uint32_t indexCount;
    uint32_t instanceCount;
    uint32_t firstIndex;
    int32_t  baseVertex;
    uint32_t baseInstance;
};

struct GPULight 
{
    float posX;
    float posY;
    float posZ;
    float colorR;
    float colorG;
    float colorB;
    float strength;
    float radius;
    int shadowMapIndex;
    int contributesToGI;
    int lightVolumeMode; // 0 is via cubemap, 1 is via pos/radius
    int lightVolumeAABBIsDirty;
};

struct RenderItem2D
{
    glm::mat4 modelMatrix = glm::mat4(1);
    float colorTintR = 0.0f;
    float colorTintG = 0.0f;
    float colorTintB = 0.0f;
    int textureIndex = 0;
};

struct RenderItem3D 
{
    glm::mat4 modelMatrix = glm::mat4(1);
    glm::mat4 inverseModelMatrix = glm::mat4(1);

    int meshIndex;
    int baseColorTextureIndex;
    int normalMapTextureIndex;
    int rmaTextureIndex;

    int vertexOffset;
    int indexOffset;
    int castShadow = 1;             // if 0 then currently also it is not included in the TLAS
    int useEmissiveMask = 0;
    
    glm::vec3 emissiveColor = glm::vec3(0);
    glm::vec3 aabbMin = glm::vec3(0);
    glm::vec3 aabbMax = glm::vec3(0);

    float padding0;
    float padding1;
    float padding2;

    // Overloading < operator for sorting with std::sort
    bool operator<(const RenderItem3D& obj) const 
    {
        return meshIndex < obj.meshIndex;
    }
};

/*
struct RenderItem3D {
struct RenderItem3D {

    glm::mat4 modelMatrix = glm::mat4(1);
    glm::mat4 inverseModelMatrix = glm::mat4(1);

    int meshIndex;
    int materialIndex;
    int vertexOffset;
    int indexOffset;

    int castShadow = 1;             // if 0 then currently also it is not included in the TLAS
    int useEmissiveMask = 0;
    int isGold = 0;

    glm::vec3 emissiveColor = glm::vec3(0);
    glm::vec3 aabbMin;
    glm::vec3 aabbMax;

    int baseColorTextureIndex = 0;
    int normalTextureIndex = 0;
    int rmaTextureIndex = 0;
    float sphereRadius = 0;


    // Overloading < operator for sorting with std::sort
    bool operator<(const RenderItem3D& obj) const {
        return meshIndex < obj.meshIndex;
    }
};
};*/

struct CSGInstance
{
    int baseColorTextureIndex;
    int normalTextureIndex;
    int rmaTextureIndex;
    int padding;
};

struct SkinnedRenderItem 
{
    glm::mat4 modelMatrix = glm::mat4(1);
    glm::mat4 inverseModelMatrix = glm::mat4(1);
    int originalMeshIndex = 0;
    int materialIndex = 0;
    int baseVertex = 0 ;
    int isGold = 0; // Why is it an int?
};

struct CameraData 
{
    glm::mat4 projection = glm::mat4(1);
    glm::mat4 projectionInverse = glm::mat4(1);
    glm::mat4 view = glm::mat4(1);
    glm::mat4 viewInverse = glm::mat4(1);

    float viewportWidth = 0;
    float viewportHeight = 0;
    float viewportOffsetX = 0;
    float viewportOffsetY = 0;

    float clipSpaceXMin;
    float clipSpaceXMax;
    float clipSpaceYMin;
    float clipSpaceYMax;

    float contrast;
    float colorMultiplierR;
    float colorMultiplierG;
    float colorMultiplierB;
};

struct BoundingBox 
{
    glm::vec3 size;
    glm::vec3 offsetFromModelOrigin;
};

struct Vertex 
{
    Vertex() = default;

    Vertex(glm::vec3 pos) 
    {
        position = pos;
    }

    Vertex(glm::vec3 pos, glm::vec3 norm)
    {
        position = pos;
        normal = norm;
    }

    glm::vec3 position = glm::vec3(0);
    glm::vec3 normal = glm::vec3(0);
    glm::vec2 uv = glm::vec2(0);
    glm::vec3 tangent = glm::vec3(0);

    bool operator==(const Vertex& other) const 
    {
        return position == other.position && normal == other.normal && uv == other.uv;
    }
};

struct WeightedVertex 
{
    glm::vec3 position = glm::vec3(0);
    glm::vec3 normal = glm::vec3(0);
    glm::vec2 uv = glm::vec2(0);
    glm::vec3 tangent = glm::vec3(0);
    glm::ivec4 boneID = glm::ivec4(0);
    glm::vec4 weight = glm::vec4(0);

    bool operator==(const Vertex& other) const 
    {
        return position == other.position && normal == other.normal && uv == other.uv;
    }
};

struct DebugVertex 
{
    glm::vec3 position = glm::vec3(0);
    glm::vec3 color = glm::vec3(0);
};

struct CSGVertex 
{
    CSGVertex() = default;

    CSGVertex(glm::vec3 pos) 
    {
        position = pos;
    }

    CSGVertex(glm::vec3 pos, glm::vec3 norm) 
    {
        position = pos;
        normal = norm;
    }

    glm::vec3 position = glm::vec3(0);
    glm::vec3 normal = glm::vec3(0);
    glm::vec2 uv = glm::vec2(0);
    glm::vec3 tangent = glm::vec3(0);

    int materialIndex = 0;
};

/*
namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.position) ^ (hash<glm::vec3>()(vertex.normal) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.uv) << 1);
        }
    };
}*/

namespace std 
{
    template<> struct hash<Vertex> 
    {
        size_t operator()(Vertex const& vertex) const 
        {
            size_t h1 = hash<glm::vec3>()(vertex.position);
            size_t h2 = hash<glm::vec3>()(vertex.normal);
            size_t h3 = hash<glm::vec2>()(vertex.uv);
            return h1 ^ (h2 << 1) ^ (h3 << 2);  // Combining the hashes
        }
    };
}

struct CloudPointOld 
{
    glm::vec4 position = glm::vec4(0);
    glm::vec4 normal = glm::vec4(0);
    glm::vec4 directLighting = glm::vec4(0);
};

enum DebugLineRenderMode 
{
    SHOW_NO_LINES,
    PATHFINDING_RECAST,
    PHYSX_ALL,
    PHYSX_RAYCAST,
    PHYSX_COLLISION,
    RAYTRACE_LAND,
    PHYSX_EDITOR,
    BOUNDING_BOXES,
    RTX_LAND_AABBS,
    RTX_LAND_TRIS,
    RTX_LAND_TOP_LEVEL_ACCELERATION_STRUCTURE,
    RTX_LAND_BOTTOM_LEVEL_ACCELERATION_STRUCTURES,
    RTX_LAND_TOP_AND_BOTTOM_LEVEL_ACCELERATION_STRUCTURES,
    DEBUG_LINE_MODE_COUNT,
};

enum RenderMode
{
    COMPOSITE,
    DIRECT_LIGHT,
    POINT_CLOUD,
    COMPOSITE_PLUS_POINT_CLOUD,
    TILE_HEATMAP,
    LIGHTS_PER_TILE,
    LIGHTS_PER_PIXEL,
    RENDER_MODE_COUNT
};

struct CloudPoint 
{
    glm::vec3 position = glm::vec3(0);
    glm::vec3 normal = glm::vec3(0);
    glm::vec3 directLighting = glm::vec3(0);
    glm::vec3 padding;
};