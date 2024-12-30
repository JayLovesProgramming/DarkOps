#pragma once

#include "HellCommon.hpp"
#include "Enums.hpp"

constexpr static auto MENU_SELECT_AUDIO = "SELECT.wav";
constexpr static auto MENU_SELECT_VOLUME = 1.0f;

namespace Editor 
{
    enum class InteractionType
    {
        HOVERED,
        SELECTED
    };

    struct MenuItem
    {
        std::string name;
        enum class Type
        {
            // Do these VALUE_ members need to be here? Doesn't really make sense to me
            VALUE_INT,
            VALUE_FLOAT,
            VALUE_STRING,
            VALUE_BOOL,

            INSERT_CSG_ADDITIVE,
            INSERT_WALL_PLANE,
            INSERT_CEILING_PLANE,
            INSERT_FLOOR_PLANE,
            INSERT_CSG_SUBTRACTIVE,
            INSERT_DOOR,
            INSERT_WINDOW,
            INSERT_LIGHT,

            CLOSE_MENU,

            FILE_NEW_MAP,
            FILE_LOAD_MAP,
            FILE_SAVE_MAP,

            RECALCULATE_NAV_MESH,
            RECALCULATE_GI
        } type;

        // We need to learn what this ptr variable is doing?
        void* ptr;

        float increment = 1.0f;
        int precision = 2;
    };

    static struct ClipBoard
    {
        int materialIndex = -1;
        float textureScale = 0;
        float textureOffsetX = 0;
        float textureOffsetY = 0;
    } g_clipBoard;

    static ObjectType g_hoveredObjectType = ObjectType::UNDEFINED;
    static ObjectType g_selectedObjectType = ObjectType::UNDEFINED;
    static std::vector<RenderItem3D> gHoveredRenderItems;
    static std::vector<RenderItem3D> gSelectedRenderItems;
    static std::vector<RenderItem2D> gMenuRenderItems;
    static std::vector<RenderItem2D> gEditorUIRenderItems;
    static std::vector<MenuItem> g_menuItems;

    static std::string g_debugText = "";
    static int g_menuSelectionIndex = 0;
    //bool g_insertMenuOpen = false;
    //bool g_fileMenuOpen = false;
    static MenuType g_currentMenuType = MenuType::NONE;
    static bool g_isDraggingMenu = false;
    static hell::ivec2 g_menuLocation = hell::ivec2(76, 460);
    static hell::ivec2 g_backgroundLocation = hell::ivec2(0, 0);
    static hell::ivec2 g_backgroundSize = hell::ivec2(0, 0);
    static hell::ivec2 g_dragOffset = hell::ivec2(0, 0);

    // Not a big deal but really figure out why these global variables below need to be static
    static glm::mat4 g_editorViewMatrix;
    static glm::dvec3 g_viewTarget;
    static glm::dvec3 g_camPos;

    static double g_yawAngle = 0.0;
    static double g_pitchAngle = 0.0;

    static bool g_editorOpen = false;
    //bool g_objectIsSelected = false;

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
    void HideGizmo();
    void CheckVertexHover(glm::mat4 mvp);
    void CheckForVertexSelection();
    void UpdateSelectedObjectGizmo();
    void UpdateSelectedVertexPosition();
    bool FloatWithinRange(float a, float b, float threshold);
    void UpdateVertexObjectGizmo();
    void EvaluateCopyAndPaste();

    // Rendering
    void ClearRenderItems();
    void UpdateRenderItemsPlease();
    std::vector<RenderItem3D>& GetHoveredRenderItems();
    std::vector<RenderItem3D>& GetSelectedRenderItems();
    std::vector<RenderItem2D>& GetMenuRenderItems();
    std::vector<RenderItem2D>& GetEditorUIRenderItems();

    // Asset Browser
    void PutDownCSGAdditive();

    glm::dvec3 Rot3D(glm::dvec3 v, glm::dvec2 rot);
    void UpdateRenderItems(std::vector<RenderItem3D>& renderItems, InteractionType interactionType, int index);
    void RebuildEverything();
    void UpdateMenu();
    //void UpdateDebugText();
    bool MenuHasHover();

}