#pragma once

#include "RendererCommon.hpp"
#include "Types/DetachedMesh.hpp"
#include "Math/Frustum.hpp"

namespace Renderer
{
    static std::string g_debugText = "";

    static AABB g_testAABB = {
        glm::vec3(-0.75f, 0.75f, -0.25f),
        glm::vec3(-0.25f, 1.25f, 0.25f)
    };

    static Sphere g_testSphere = {
        glm::vec3(0.5f, 1.0f, 0.0f),
        0.35f
    };

    inline std::vector<DebugLineRenderMode> _allowedDebugLineRenderModes = {
        SHOW_NO_LINES,
        //PATHFINDING,
        PHYSX_COLLISION,
        PATHFINDING_RECAST,
        RTX_LAND_TOP_LEVEL_ACCELERATION_STRUCTURE,
        RTX_LAND_BOTTOM_LEVEL_ACCELERATION_STRUCTURES,
        BOUNDING_BOXES,
    };



    //void RenderLoadingScreen();
    void RenderFrame();
    void HotloadShaders();
    void NextRenderMode();
    void PreviousRenderMode();
    void NextDebugLineRenderMode();
    void UpdatePointCloud();
    void RecreateBlurBuffers();
    RenderMode GetRenderMode();
    DebugLineRenderMode GetDebugLineRenderMode();
    void ToggleProbes();
    bool ProbesVisible();

    // Debug
    void UpdateDebugLinesMesh();
    void UpdateDebugLinesMesh2D();
    void UpdateDebugPointsMesh();
    void UpdateDebugTrianglesMesh();
    //glm::vec4 ExtractLeftFrustumPlane(const glm::mat4& viewProj);
    void DrawLine(glm::vec3 begin, glm::vec3 end, glm::vec3 color);
    void DrawAABB(AABB& aabb, glm::vec3 color);
    void DrawAABB(AABB& aabb, glm::vec3 color, glm::mat4 worldTransform);
    void DrawSphere(const Sphere& sphere, int segments, const glm::vec3& color);
    void DrawFrustum(Frustum& frustum, glm::vec3 color);
    std::string& GetDebugText();
    inline DetachedMesh g_debugLinesMesh;
    inline DetachedMesh g_debugLinesMesh2D;
    inline DetachedMesh g_debugPointsMesh;
    inline DetachedMesh g_debugTrianglesMesh;
    inline std::vector<Vertex> g_debugLines;
    inline DebugLineRenderMode g_debugLineRenderMode = DebugLineRenderMode::SHOW_NO_LINES;
};