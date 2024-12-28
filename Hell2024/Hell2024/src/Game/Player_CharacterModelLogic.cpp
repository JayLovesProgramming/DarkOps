#include "Player.hpp"

void Player::UpdateCharacterModelAnimation(float deltaTime)
{
    WeaponInfo* weaponInfo = GetCurrentWeaponInfo();
    WeaponState* weaponState = GetCurrentWeaponState();
    AnimatedGameObject* character = GetCharacterAnimatedGameObject();

    character->EnableDrawingForAllMesh();

    if (IsDead())
    {
        HideKnifeMesh();
        HideGlockMesh();
        HideShotgunMesh();
        HideAKS74UMesh();
        return;
    }

    if (weaponInfo->type == WeaponType::MELEE)
    {
        // Hide all unnecessary weapon meshes
        HideAKS74UMesh();
        HideGlockMesh();
        HideShotgunMesh();

        character->PlayAndLoopAnimation(
            IsMoving() ? "UnisexGuy_Knife_Walk" : "UnisexGuy_Knife_Idle", // If we are moving, apply the walk animation
            1.0f
        );

        if (IsCrouching()) 
        {
            character->PlayAndLoopAnimation("UnisexGuy_Knife_Crouch", 1.0f);
        }
    }

    if (weaponInfo->type == WeaponType::PISTOL)
    {
        HideAKS74UMesh();
        HideShotgunMesh();
        HideKnifeMesh();

        character->PlayAndLoopAnimation(
            IsMoving() ? "UnisexGuy_Glock_Walk" : "UnisexGuy_Glock_Idle", // If we are moving, apply the walk animation
            1.0f
        );

        if (IsCrouching()) 
        {
            character->PlayAndLoopAnimation("UnisexGuy_Glock_Crouch", 1.0f);
        }
    }

    if (weaponInfo->type == WeaponType::AUTOMATIC)
    {
        HideShotgunMesh();
        HideKnifeMesh();
        HideGlockMesh();

        character->PlayAndLoopAnimation(
            IsMoving() ? "UnisexGuy_AKS74U_Walk" : "UnisexGuy_AKS74U_Idle", // If we are moving, apply the walk animation
            1.0f
        );
    
        if (IsCrouching()) 
        {
            character->PlayAndLoopAnimation("UnisexGuy_AKS74U_Crouch", 1.0f);
        }
    }

    if (weaponInfo->type == WeaponType::SHOTGUN)
    {
        HideAKS74UMesh();
        HideKnifeMesh();
        HideGlockMesh();

        character->PlayAndLoopAnimation(
            IsMoving() ? "UnisexGuy_Shotgun_Walk" : "UnisexGuy_Shotgun_Idle", // If we are moving, apply the walk animation
            1.0f
        );

        if (IsCrouching()) 
        {
            character->PlayAndLoopAnimation("UnisexGuy_Shotgun_Crouch", 1.0f);
        }
    }

    character->SetPosition(GetFeetPosition());// +glm::vec3(0.0f, 0.1f, 0.0f));
    character->Update(deltaTime);
    character->SetRotationY(_rotation.y + DARKOPS_PI);
}

void Player::HideKnifeMesh() const
{
    AnimatedGameObject* character = GetCharacterAnimatedGameObject();
    character->DisableDrawingForMeshByMeshName("SM_Knife_01");
}

void Player::HideGlockMesh() const
{
    AnimatedGameObject* character = GetCharacterAnimatedGameObject();
    character->DisableDrawingForMeshByMeshName("Glock");
}

void Player::HideShotgunMesh() const
{
    AnimatedGameObject* character = GetCharacterAnimatedGameObject();
    character->DisableDrawingForMeshByMeshName("Shotgun_Mesh");
}

void Player::HideAKS74UMesh() const
{
    AnimatedGameObject* character = GetCharacterAnimatedGameObject();
    character->DisableDrawingForMeshByMeshName("FrontSight_low");
    character->DisableDrawingForMeshByMeshName("Receiver_low");
    character->DisableDrawingForMeshByMeshName("BoltCarrier_low");
    character->DisableDrawingForMeshByMeshName("SafetySwitch_low");
    character->DisableDrawingForMeshByMeshName("MagRelease_low");
    character->DisableDrawingForMeshByMeshName("Pistol_low");
    character->DisableDrawingForMeshByMeshName("Trigger_low");
    character->DisableDrawingForMeshByMeshName("Magazine_Housing_low");
    character->DisableDrawingForMeshByMeshName("BarrelTip_low");
}