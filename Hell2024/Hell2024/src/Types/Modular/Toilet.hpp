#pragma once

#include "HellCommon.hpp"
#include "API/OpenGL/Types/GL_Shader.hpp"
#include "Core/AssetManager.hpp"
#include "Game/GameObject.hpp"

struct Toilet
{
    Transform transform;

    Toilet() = default;

    Toilet(glm::vec3 position, float rotation);

    void Draw(Shader& shader, bool bindMaterial = true);
    void Update(float deltaTime);
    glm::mat4 GetModelMatrix();
    void CleanUp();
};