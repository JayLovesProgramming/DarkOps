#pragma once

#include "HellCommon.hpp"
#include "Enums.hpp"

constexpr static auto MENU_SELECT_AUDIO = "SELECT.wav";
constexpr static auto MENU_SELECT_VOLUME = 1.0f;

namespace Editor 
{
    // Not a big deal but really figure out why these 3 global variables below need to be static
    static glm::mat4 g_editorViewMatrix;
    static glm::dvec3 g_viewTarget;
    static glm::dvec3 g_camPos;

    inline int g_hoveredObjectIndex = 0;
    inline int g_selectedObjectIndex = 0;
    inline int g_hoveredVertexIndex = 0; // ranges from 0 to 3 for planes
    inline int g_selectedVertexIndex = 0;
    inline glm::mat4 g_gizmoMatrix = glm::mat4(1);
    inline glm::vec3 g_hoveredVertexPosition;
    inline glm::vec3 g_selectedVertexPosition;

    constexpr double g_orbitRadius = 2.5f;
    constexpr double g_orbiteSpeed = 0.003f;
    constexpr double g_zoomSpeed = 0.5f;
    constexpr double g_panSpeed = 0.004f;

    void EnterEditor();
    void LeaveEditor();
    void Update(float deltaTime);
    bool IsOpen();
    bool ObjectIsSelected();
    bool ObjectIsHoverered();
    std::string& GetDebugText();
    ObjectType& GetHoveredObjectType();
    ObjectType& GetSelectedObjectType();
    uint32_t GetSelectedObjectIndex();
    uint32_t GetHoveredObjectIndex();
    glm::mat4& GetViewMatrix();
    glm::vec3 GetViewPos();
    glm::vec3 GetSelectedVertexPosition();
    glm::vec3 GetHoveredVertexPosition();
    int GetSelectedVertexIndex();
    int GetHoveredVertexIndex();

    MenuType GetCurrentMenuType();
    void SetCurrentMenuType(MenuType type);

    // Rendering
    void UpdateRenderItems();
    std::vector<RenderItem3D>& GetHoveredRenderItems();
    std::vector<RenderItem3D>& GetSelectedRenderItems();
    std::vector<RenderItem2D>& GetMenuRenderItems();
    std::vector<RenderItem2D>& GetEditorUIRenderItems();

    // Asset Browser
    void PutDownCSGAdditive();
}