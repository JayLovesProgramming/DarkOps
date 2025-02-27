#pragma once

#include "HellCommon.hpp"

namespace BackEnd 
{
    extern std::string _windowName;

    // Core
    void Init(API api);
    void BeginFrame();
    void UpdateSubSystems();
    void EndFrame();
    void CleanUp();

    // API
    void SetAPI(API api);
    const API GetAPI();

    // Window
    GLFWimage LoadWindowIcon(const std::string& iconPath);
    GLFWwindow* GetWindowPointer();
    const WindowedMode& GetWindowMode();
    void SetWindowPointer(GLFWwindow* window);
    void CreateGLFWWindow(const WindowedMode& windowedMode);
    void SetWindowedMode(const WindowedMode& windowedMode);
    void ToggleFullscreen();
    void ForceCloseWindow();
    bool WindowIsOpen();
    bool WindowHasFocus();
    bool WindowHasNotBeenForceClosed();
    bool WindowIsMinimized();
    int GetWindowedWidth();
    int GetWindowedHeight();
    int GetCurrentWindowWidth();
    int GetCurrentWindowHeight();
    int GetFullScreenWidth();
    int GetFullScreenHeight();

    // Render Targets
    void SetPresentTargetSize(int width, int height);
    int GetPresentTargetWidth();
    int GetPresentTargetHeight();
}