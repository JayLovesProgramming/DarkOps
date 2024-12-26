#pragma once

#include "../../vendor/im3d/im3d.h"
#include "API/OpenGL/Types/GL_Shader.hpp"
#include "Input/Input.hpp"

namespace Gizmo
{
    inline GLuint g_Im3dVertexArray;
    inline GLuint g_Im3dVertexBuffer;
    inline GLuint g_Im3dShaderPoints;
    inline GLuint g_Im3dShaderLines;
    inline GLuint g_Im3dShaderTriangles;
    inline Shader g_TriangleShader;
    inline Shader g_LineShader;
    inline Shader g_PointShader;
    inline Im3d::Mat4 g_transform = (1.0f);

    inline bool _inUse = false;

    void Init();

    void CleanUp();

    bool HasHover();

    void ResetHover();

    bool InUse();

    Im3d::Mat4& GetTransform();

    glm::mat4 Im3dMat4ToGlmMat4(Im3d::Mat4 pxMatrix);

    Im3d::Mat4 GlmMat4ToIm3dMat4(glm::mat4 glmMatrix);

    glm::vec3 GetMouseRay(glm::mat4 projection, glm::mat4 view, int windowWidth, int windowHeight, int mouseX, int mouseY);

    glm::vec3 GetTranslationFromMatrix666(glm::mat4 matrix);

    float Radians(float _degrees);

    #define if_likely(e)   if(!!(e))

    Im3d::Vec3 ToEulerXYZ(const Im3d::Mat3& _m);

    Transform Update(glm::vec3 viewPos, glm::vec3 viewDir, float mouseX, float mouseY, glm::mat4 projection, glm::mat4 view, bool leftMouseDown, float viewportWidth, float viewportHeight, glm::mat4 matrix);

    void Draw(glm::mat4 projection, glm::mat4 view, float viewportWidth, float viewportHeight);
}