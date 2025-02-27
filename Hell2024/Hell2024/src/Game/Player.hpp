#pragma once

#include "Weapon/WeaponManager.hpp"
#include "Game/AnimatedGameObject.hpp"
#include "Input/Keycodes.hpp"
#include "Physics/Physics.hpp"
#include "Math/Frustum.hpp"
#include "Math/Types.hpp"

constexpr static auto GLOCK_CLIP_SIZE = 12;
constexpr static auto GLOCK_MAX_AMMO_SIZE = 200;
constexpr static auto AKS74U_MAG_SIZE = 30;
constexpr static auto AKS74U_MAX_AMMO_SIZE = 9999;
constexpr static auto SHOTGUN_AMMO_SIZE = 8;
constexpr static auto SHOTGUN_MAX_AMMO_SIZE = 9999;

struct Ammo 
{
	int clip = 0;
	int total = 0;
};

struct Inventory 
{
    Ammo glockAmmo;
    Ammo aks74uAmmo;
    Ammo shotgunAmmo;
};

enum InputType 
{
    KEYBOARD_AND_MOUSE,
    CONTROLLER
};

enum CrosshairType 
{
    NONE,
    REGULAR,
    INTERACT
};

struct PickUpText
{
    std::string text;
    float lifetime;
    int count = 1;
};

enum class ShellEjectionState 
{
    IDLE, 
    AWAITING_SHELL_EJECTION
};

struct PlayerControls
{
    unsigned int WALK_FORWARD = HELL_KEY_W;
    unsigned int WALK_BACKWARD = HELL_KEY_S;
    unsigned int WALK_LEFT = HELL_KEY_A;
    unsigned int WALK_RIGHT = HELL_KEY_D;
    unsigned int INTERACT = HELL_KEY_E;
    unsigned int RELOAD = HELL_KEY_R;
    unsigned int FIRE = HELL_MOUSE_LEFT;
    unsigned int ADS = HELL_MOUSE_RIGHT;
    unsigned int JUMP = HELL_KEY_SPACE;
    unsigned int CROUCH = HELL_KEY_WIN_CONTROL; // different mapping to the standard glfw HELL_KEY_LEFT_CONTROL
    unsigned int NEXT_WEAPON = HELL_KEY_Q;
    unsigned int ESCAPE = HELL_KEY_WIN_ESCAPE;
    unsigned int DEBUG_FULLSCREEN = HELL_KEY_G;
    unsigned int DEBUG_ONE = HELL_KEY_1;
    unsigned int DEBUG_TWO = HELL_KEY_2;
    unsigned int DEBUG_THREE = HELL_KEY_3;
    unsigned int DEBUG_FOUR = HELL_KEY_4;
    unsigned int MELEE = HELL_KEY_V;
    unsigned int FLASHLIGHT = HELL_KEY_F;
};

struct AmmoState 
{
    std::string name = UNDEFINED_STRING;
    int ammoOnHand = 0;
};

class Player 
{
private:
    int32_t m_viewWeaponAnimatedGameObjectIndex = -1;
    int32_t m_characterModelAnimatedGameObjectIndex = -1;
    std::vector<PickUpText> m_pickUpTexts;
    glm::vec2 m_headBob = glm::vec2(0, 0);
    glm::vec2 m_breatheBob = glm::vec2(0, 0);
    Transform m_weaponSwayTransform;
    bool m_crouching = false;
    bool m_moving = false;
    float m_headBobTimer = 0;
    float m_breatheBobTimer = 0;
    bool m_ignoreControl = false;
    int m_killCount = 0;
    int m_suicideCount = 0;
    int m_mouseIndex = -1;
    int m_keyboardIndex = -1;
    float m_capsuleRadius = 0.1f;
    bool m_isOutside = false;
    ShellEjectionState m_shellEjectionState = {};
    PxShape* m_interactSphere = NULL;
    glm::mat4 m_casingSpawnMatrix = glm::mat4(1);
    glm::mat4 m_muzzleFlashMatrix = glm::mat4(1);
    OverlapReport m_interactOverlapReport;
    std::string overlapList;
    float m_accuracyModifer = 0;
    bool m_firedThisFrame = false;

public:

    constexpr static auto PLAYER_CAPSULE_HEIGHT = 0.4f;
    constexpr static auto PLAYER_CAPSULE_RADIUS = 0.25f;

    int32_t m_playerIndex = -1; // Can this not be 0? Can it be static and/or inline? i really need to learn


    float m_crosshairCrossSize = 0;
    glm::mat4 m_weaponSwayMatrix = glm::mat4(1);
    bool m_pickUpInteractable = false;
    bool g_awaitingRespawn = true;
    int m_interactbleGameObjectIndex = -1;
    bool m_flashlightOn = true;

    Player() = default;
    Player(int playerIndex);
    PhysXRayResult m_cameraRayResult;

    // Updates
    void UpdatePlayer1(float deltaTime);

    void UpdateRagdoll();
    void UpdateMouseLook(float deltaTime);
    void UpdateViewMatrix(float deltaTime);
    void UpdateMovement(float deltaTime);
    void UpdatePickupText(float deltaTime);
    void UpdateCharacterModelAnimation(float deltaTime);
    void UpdateTimers(float deltaTime);
    void UpdateHeadBob(float deltaTime);
    void UpdateAudio(float deltaTime);

    // Checks
    void CheckForAndEvaluateFlashlight(float deltaTime);
    void CheckForAndEvaluateInteract();
    void CheckForAndEvaluateRespawnPress();
    void CheckForAndEvaluateNextWeaponPress();
    void CheckForEnviromentalDamage(float deltaTime);
    void CheckForDeath();
    void CheckForDebugKeyPresses();
    void CheckForSuicide();
    bool IsLookingAtOtherPlayer(glm::vec3 myPos, glm::vec3 theirPos, glm::vec3 cameraForward, float maxDistance = 0.65f, float minDotProduct = 0.8f);

    // State queries
    bool IsMoving() const;
    bool IsCrouching() const;
    bool IsDead() const;
    bool IsAlive() const;
    bool HasControl() const;

    // Weapon shit
    void UpdateViewWeaponLogic(float deltaTime);
    void HandleMelee(AnimatedGameObject* viewWeapon, WeaponInfo* weaponInfo);
    void HandlePistols(AnimatedGameObject* viewWeapon, WeaponInfo* weaponInfo, WeaponState* weaponState, AmmoState* ammoState, AmmoInfo* ammoInfo, float deltaTime);
    void HandleShotguns(AnimatedGameObject* viewWeapon, WeaponInfo* weaponInfo, WeaponState* weaponState, AmmoState* ammoState, AmmoInfo* ammoInfo, float deltaTime);
    void PlayerRevolverCockSound(WeaponInfo* weaponInfo);

    WeaponInfo* GetCurrentWeaponInfo();
    WeaponState* GetWeaponStateByName(std::string name);
    WeaponState* GetCurrentWeaponState();
    AmmoState* GetAmmoStateByName(std::string name);
    void GiveWeapon(std::string name);
    void GiveAmmo(std::string name, int amount);
    void SwitchWeapon(std::string name, WeaponAction weaponAction);
    void GiveRedDotToWeapon(std::string name);
    void GiveSilencerToWeapon(std::string name);
    void DropWeapons();
    void UpdateWeaponSway(float deltaTime);
    RenderItem3D CreateAttachmentRenderItem(WeaponAttachmentInfo* weaponAttachmentInfo, const char* boneName);
    bool CanMelee();
    void CheckForMeleeHits();

    // Rando
    void Respawn();
    void EnableControl();
    void DisableControl();

private:
    std::vector<RenderItem3D> m_attachmentRenderItems;
    std::vector<RenderItem3D> m_attachmentGlassRenderItems;
public:
    void UpdateAttachmentRenderItems();
    void UpdateAttachmentGlassRenderItems();
    std::vector<RenderItem3D>& GetAttachmentRenderItems();
    std::vector<RenderItem3D>& GetAttachmentGlassRenderItems();

    // Input
    int32_t GetKeyboardIndex() const;
    void SetKeyboardIndex(int32_t index);

    int32_t GetMouseIndex() const;
    void SetMouseIndex(int32_t index);

    void RotateWeapons(bool nextWeapon);
    bool PressingWalkForward() const;
    bool PressingWalkBackward() const;
    bool PressingWalkLeft() const;
    bool PressingWalkRight() const;
    bool PressingCrouch() const;
    bool PressedWalkForward() const;
    bool PressedWalkBackward() const;
    bool PressedWalkLeft() const;
    bool PressedWalkRight() const;
    bool PressedInteract() const;
    bool PressedReload() const;
    bool PressedFire() const;
    bool PressingFire() const;
    bool PresingJump() const;
    bool PressedCrouch() const;
    bool PressedNextWeapon() const;
    bool PressedPreviousWeapon() const;
    bool PressingADS() const;
    bool PressedADS() const;
    bool PressedEscape() const;
    bool PressedMelee() const;
    bool PressedFlashlight() const;

    // Misc gameplay shit
    int32_t GetKillCount() const;
    void IncrementKillCount();

    // Misc getters
    int32_t GetViewWeaponAnimatedGameObjectIndex() const;
    int32_t GetCharacterModelAnimatedGameObjectIndex() const;
    //int32_t GetPlayerIndex();
    glm::vec3 GetMuzzleFlashPosition();
    glm::vec3 GetPistolCasingSpawnPostion();
    AnimatedGameObject* GetCharacterAnimatedGameObject() const;
    AnimatedGameObject* GetViewWeaponAnimatedGameObject() const;

    std::vector<WeaponState> m_weaponStates;
    std::vector<AmmoState> m_ammoStates;
    int m_currentWeaponIndex = 0;

    void CreateCharacterModel();
    void CreateViewModel();

public:
    Frustum m_frustum = {};

    InputType _inputType = KEYBOARD_AND_MOUSE;
    PlayerControls _controls;

	//RayCastResult _cameraRayData;
	PxController* _characterController = NULL;

    PxShape* _itemPickupOverlapShape = NULL;
    PxShape* _meleeHitCheckOverlapShape = NULL;
	//PxRigidStatic* _itemPickupOverlapDebugBody = NULL;
    float _yVelocity = 0;

	//Inventory _inventory;

	int GetCurrentWeaponMagAmmo();
	int GetCurrentWeaponTotalAmmo();
    void SetPosition(glm::vec3 position);

    bool _glockSlideNeedsToBeOut = false;
    bool _needsShotgunFirstShellAdded = false;
    bool _needsShotgunSecondShellAdded = false;

    int _health = 100;
    float _damageColorTimer = 1.0f;
    float _outsideDamageTimer = 0;
    float _outsideDamageAudioTimer = 0;

    void GiveDamageColor();

	//void Init(glm::vec3 position);

	void SetRotation(glm::vec3 rotation);
	//void SetWeapon(Weapon weapon);
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetInverseViewMatrix() const;
	glm::vec3 GetViewPos() const;
	glm::vec3 GetViewRotation() const;
	glm::vec3 GetFeetPosition() const;
	glm::vec3 GetCameraRight() const;
	glm::vec3 GetCameraForward() const;
	glm::vec3 GetCameraUp() const;
    //int GetCurrentWeaponIndex();

    //void UpdateViewWeaponLogicAndAnimations(float deltaTime);
	void SpawnMuzzleFlash();
    void SpawnCasing(AmmoInfo* ammoInfo);
	float GetMuzzleFlashTime() const;
	float GetMuzzleFlashRotation() const;
	float GetRadius() const;
	void CreateCharacterController(glm::vec3 position);
	//void WipeYVelocityToZeroIfHeadHitCeiling();
	PxShape* GetCharacterControllerShape() const;
	PxRigidDynamic* GetCharacterControllerActor() const;
	void CreateItemPickupOverlapShape();
	PxShape* GetItemPickupOverlapShape() const;

	void AddPickUpText(std::string text, int count);
    //void PickUpAKS74U();
    //void PickUpAKS74UAmmo();
    //void PickUpShotgunAmmo();
    //void PickUpGlockAmmo();
	//void CastMouseRay();
	//void DropAKS7UMag();
    void CheckForMeleeHit();

    //void SetGlockAnimatedModelSettings();

	//ShadowMap _shadowMap;
	float _muzzleFlashCounter = 0;

	bool MuzzleFlashIsRequired() const;
	glm::mat4 GetWeaponSwayMatrix() const;
    WeaponAction& GetWeaponAction();

    //glm::vec3 GetGlockBarrelPosition();

	bool _isGrounded = true;

    //void PickUpShotgun();

    glm::mat4 GetProjectionMatrix() const;
    float GetZoom() const;

    bool CanEnterADS();
    bool InADS() const;

	//std::string _pickUpText = "";
	//float _pickUpTextTimer = 0;
    float _zoom = 1.0f;

    //void LoadWeaponInfo(std::string name, WeaponAction weaponAction);

    float finalImageContrast = 1.0f;
    glm::vec3 finalImageColorTint = glm::vec3(0);

    // Dev keys
    bool PressedFullscreen() const;
    bool PressedOne() const;
    bool PressedTwo() const;
    bool PressedThree() const;
    bool PressedFour() const;

    glm::vec3 GetCameraRotation() const;

    void HideKnifeMesh() const;
    void HideGlockMesh() const;
    void HideShotgunMesh() const;
    void HideAKS74UMesh() const;
    void Kill();
    PxU32 _interactFlags;
    PxU32 _bulletFlags;
    std::string _playerName;
    bool _isDead = false;
    glm::vec3 _movementVector = glm::vec3(0);
    float _timeSinceDeath = 0;
    bool _isOutside = false;

    float _currentSpeed = 0.0f;

    void ForceSetViewMatrix(glm::mat4 viewMatrix);
    std::vector<RenderItem2D> GetHudRenderItems(hell::ivec2 presentSize);
    std::vector<RenderItem2D> GetHudRenderItemsHiRes(hell::ivec2 gBufferSize);
    CrosshairType GetCrosshairType() const;

    bool RespawnAllowed() const;
    std::vector<RenderItem2D> renderItems;

private:
    glm::vec3 _displacement;

	void SpawnBullet(float variance, Weapon type);
	bool CanFire();
	bool CanReload();
    void ReloadWeapon(AnimatedGameObject* viewWeapon, WeaponInfo* weaponInfo, WeaponState* weaponState);
	void CheckForItemPickOverlaps();

	bool _needsToDropAKMag = false;

    float _footstepAudioTimer = 0;
    float _footstepAudioLoopLength = 0.5;

	glm::vec3 _position = glm::vec3(0);
	glm::vec3 _rotation = glm::vec3(-0.1f, -DARKOPS_PI * 0.5f, 0);
	float _viewHeightStanding = 1.65f;
	float _viewHeightCrouching = 1.15f;
	float _crouchDownSpeed = 17.5f;
	float _currentViewHeight = _viewHeightStanding;
	float _walkingSpeed = 4.85f;
	float _crouchingSpeed = 2.325f;
	glm::mat4 _viewMatrix = glm::mat4(1);
	glm::mat4 _inverseViewMatrix = glm::mat4(1);
	glm::vec3 _viewPos = glm::vec3(0);
	glm::vec3 _forward = glm::vec3(0);
	glm::vec3 _up = glm::vec3(0);
	glm::vec3 _right = glm::vec3(0);

	float _muzzleFlashRotation = 0;
	//int _currentWeaponIndex = 0;
	WeaponAction _weaponAction = DRAW_BEGIN;
	bool _needsRespawning = true;
	glm::vec2 _weaponSwayFactor = glm::vec2(0);
    glm::vec3 _weaponSwayTargetPos = glm::vec3(0);
    bool _needsAmmoReloaded = false;
    bool m_revolverNeedsCocking = false;
    int m_revolverReloadIterations = 0;

public:
    float _muzzleFlashTimer = 0;
};