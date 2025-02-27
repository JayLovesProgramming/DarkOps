#pragma once

enum class API 
{ 
    OPENGL, 
    VULKAN, 
    UNDEFINED 
};

enum class WindowedMode 
{ 
    WINDOWED,
    FULLSCREEN 
};

enum class SplitscreenMode 
{ 
    NONE, 
    TWO_PLAYER, 
    FOUR_PLAYER, 
    SPLITSCREEN_MODE_COUNT 
};

enum class BulletHoleDecalType 
{ 
    REGULAR, 
    GLASS, 
    KNIFE 
};

enum class PickUpType 
{ 
    NONE, 
    AMMO, 
    GLOCK, 
    GLOCK_AMMO, 
    TOKAREV_AMMO, 
    SHOTGUN, 
    SHOTGUN_AMMO, 
    AKS74U, 
    AKS74U_AMMO, 
    AKS74U_SCOPE 
};

enum class DobermannState 
{ 
    LAY, 
    PATROL,
    KAMAKAZI,
    DOG_SHAPED_PIECE_OF_MEAT,
    RETURN_TO_ORIGIN,
    WALK_TO_TARGET 
};

enum class FacingDirection 
{ 
    LEFT, 
    RIGHT, 
    ALIGNED 
};

enum class AABBLightVolumeMode 
{ 
    WORLDSPACE_CUBE_MAP, 
    POSITION_RADIUS 
};

enum class MenuType 
{
    NONE, 
    FILE,
    INSERT, 
    SELECTED_OBJECT, 
    MISC 
};

enum EngineMode 
{ 
    GAME = 0, 
    FLOORPLAN, 
    EDITOR 
};

enum Weapon 
{ 
    KNIFE = 0, 
    GLOCK, 
    SHOTGUN, 
    AKS74U, 
    MP7, 
    WEAPON_COUNT
};

enum WeaponAction 
{
    IDLE = 0,
    FIRE,
    RELOAD,
    RELOAD_FROM_EMPTY,
    DRAW_BEGIN,
    DRAWING,
    SPAWNING,
    RELOAD_SHOTGUN_BEGIN,
    RELOAD_SHOTGUN_SINGLE_SHELL,
    RELOAD_SHOTGUN_DOUBLE_SHELL,
    RELOAD_SHOTGUN_END,
    RELOAD_REVOLVER_BEGIN,
    RELOAD_REVOLVER_LOOP,
    RELOAD_REVOLVER_END,
    ADS_IN,
    ADS_OUT,
    ADS_IDLE,
    ADS_FIRE,
    MELEE
};

enum RaycastGroup 
{
    RAYCAST_DISABLED = 0,
    RAYCAST_ENABLED = 1,
    PLAYER_1_RAGDOLL = 2,
    PLAYER_2_RAGDOLL = 4,
    PLAYER_3_RAGDOLL = 8,
    PLAYER_4_RAGDOLL = 16,
    DOBERMAN = 32
};

enum class ObjectType 
{
    UNDEFINED,
    GAME_OBJECT,
    GLASS,
    DOOR,
    WINDOW,
    SCENE_MESH,
    RAGDOLL_RIGID,
    CSG_OBJECT_ADDITIVE_CUBE,
    CSG_OBJECT_ADDITIVE_WALL_PLANE,
    CSG_OBJECT_ADDITIVE_FLOOR_PLANE,
    CSG_OBJECT_ADDITIVE_CEILING_PLANE,
    CSG_OBJECT_SUBTRACTIVE,
    LIGHT,
    HEIGHT_MAP,
};

enum CollisionGroup 
{
    NO_COLLISION = 0,
    BULLET_CASING = 1,
    PLAYER = 2,
    ENVIROMENT_OBSTACLE = 4,
    GENERIC_BOUNCEABLE = 8,
    ITEM_PICK_UP = 16,
    RAGDOLL = 32,
    DOG_CHARACTER_CONTROLLER = 64,
    GENERTIC_INTERACTBLE = 128,
};

enum class LoadingState
{
    AWAITING_LOADING_FROM_DISK,
    LOADING_FROM_DISK,
    LOADING_COMPLETE
};

enum class BakingState
{
    AWAITING_BAKE,
    BAKE_COMPLETE
};