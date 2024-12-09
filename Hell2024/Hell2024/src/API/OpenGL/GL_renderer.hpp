// GL_renderer.hpp
#pragma once

#include "HellCommon.hpp"
#include "Renderer/RenderData.hpp"

namespace OpenGLRenderer 
{
    inline static bool drawBlueAroundModels = false;
    constexpr inline static float minPickUpDistance = 1.5f;

    void Init_OpenGL();
    void RenderLoadingScreen(std::vector<RenderItem2D>& renderItems);
    void RenderFrame(RenderData& renderData);
    void HotloadShaders();
    void BindBindlessTextures();
    void CreatePlayerRenderTargets(int presentWidth, int presentHeight);
    void UpdatePointCloud();
    void PresentFinalImage();
    void RecreateBlurBuffers();
    void QueryAvaliability();
    void CreateBlackBox(BlitDstCoords* blitDstCoords);
}