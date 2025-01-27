#include "BackEnd.hpp"
#include "GameWindow.hpp"

// API
#include "API/OpenGL/GL_BackEnd.hpp"
#include "API/OpenGL/GL_renderer.hpp"
#include "API/Vulkan/VK_backEnd.h"

// CORE
#include "Core/AssetManager.hpp"
#include "Core/Audio.hpp"
//#include "Core/ImageManager.hpp"

// EDITOR
#include "Editor/CSG.hpp"
#include "Editor/Gizmo.hpp"

// GAME
#include "Weapon/WeaponManager.hpp"

// INPUT
#include "Input/Input.hpp"
#include "Input/InputMulti.hpp"

// PHYSICS
#include "Physics/Physics.hpp"

// PHYSICS
#include "Pathfinding/Pathfinding2.hpp"

// RENDERER
#include "Renderer/ImGui/F8Console.hpp"

// START SCREEN
#include "LoadingScreen/StartScreen.hpp"

// CEF
//#include "Renderer/CEF/CEF.h"

namespace BackEnd 
{
    API _api = API::UNDEFINED;

    GLFWwindow* _window = NULL;

    WindowedMode _windowedMode = WindowedMode::WINDOWED;

    GLFWmonitor* _monitor;

    const GLFWvidmode* _mode;

    bool _forceCloseWindow = false;
    bool _windowHasFocus = true;

    int _windowedWidth = 0;
    int _windowedHeight = 0;

    int _fullscreenWidth = 0;
    int _fullscreenHeight = 0;

    int _currentWindowWidth = 0;
    int _currentWindowHeight = 0;

    int _presentTargetWidth = 0;
    int _presentTargetHeight = 0;

    int _windowPositionY = 0;
    int _windowPositionX = 0;

    std::string _windowName = "Dark Ops : Zombies";

    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void window_focus_callback(GLFWwindow* window, int focused);

    GLFWimage LoadWindowIcon(const std::string& iconPath)
    {
        GLFWimage icon = {};
        int channels;
        icon.pixels = stbi_load(iconPath.c_str(), &icon.width, &icon.height, &channels, 4);

        if (!icon.pixels)
        {
            std::cerr << "Failed to load window icon: " << iconPath << "\n";
            icon.width = 0;
            icon.height = 0;
            icon.pixels = nullptr;
        }

        return icon;
    }

    void Init(API api) 
    {
        _api = api;

        if (_api == API::UNDEFINED)
        {
            std::cerr << "[error] API is undefined" << std::endl;
            return;
        }
        else if (_api == API::VULKAN)
        {
            VulkanBackEnd::CreateVulkanInstance();
        }

        glfwInit();

        glfwSetErrorCallback([](int error, const char* description) 
        { 
            std::cerr << "GLFW Error (" << std::to_string(error) << "): " << description << "/n";
        });

        InitWindowHints();

        // Resolution and window size
        _monitor = glfwGetPrimaryMonitor();
        _mode = glfwGetVideoMode(_monitor);

        glfwWindowHint(GLFW_RED_BITS, _mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, _mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, _mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, _mode->refreshRate);

        // _mode-> width - 1920 
        // _mode -> height - 1080
        _fullscreenWidth = _mode->width; 
        _fullscreenHeight = _mode->height;

        _windowedWidth = _mode->width * 0.9;
        _windowedHeight = _mode->height * 0.9;

        CreateGLFWWindow(WindowedMode::WINDOWED);

        if (_window == NULL) 
        {
            std::cerr << "Failed to create GLFW window" << "/n";
            glfwTerminate();
            return;
        }

        glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
        glfwSetWindowFocusCallback(_window, window_focus_callback);

        if (GetAPI() == API::OPENGL) 
        {
            AssetManager::FindAssetPaths();
            glfwMakeContextCurrent(_window);
            OpenGLBackEnd::InitMinimum();
            OpenGLRenderer::Init_OpenGL();
            Gizmo::Init();
            glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE); // ? What does this do exactly?
        }
        else if (GetAPI() == API::VULKAN)
        {
            VulkanBackEnd::InitMinimum();
            // VulkanRenderer minimum init is tangled in the above function
        }

        AssetManager::LoadFont();

        if (GetAPI() == API::VULKAN)
        {
            AssetManager::FindAssetPaths();
        }

        // Init sub-systems
        Input::Init();
        Audio::Init();
        Physics::Init();
        InputMulti::Init();
        CSG::Init();
        Pathfinding2::Init();
        WeaponManager::Init();
        StartScreen::Init();
        IMGUI::Init(_window);
        glfwHideWindow(_window);

        //HINSTANCE hInstance = GetModuleHandle(NULL);

       /* if (!InitCEF(hInstance))
        {
            std::cerr << "[ERROR] CEF Init Failed" << std::endl;
            return;
        }
        else
        {
            std::cout << "[INITIALIZED] CEF" << std::endl;
        }*/

        std::cout << "[INITIALIZED] Backend" << std::endl;
    }

    void BeginFrame() 
    {
        glfwPollEvents();
    }

    void EndFrame()
    {
        //IMGUI::MainLoop();

        // OpenGL
        if (GetAPI() == API::OPENGL) 
        {
            glfwSwapBuffers(_window);
        }
        // Vulkan
        else if (GetAPI() == API::VULKAN)
        {
        }
    }

    void UpdateSubSystems()
    {
        Input::Update();
        Audio::Update();
        //Scene::Update();
    }

    void CleanUp() 
    {
        IMGUI::Destroy();

        if (GetWindowMode() == WindowedMode::FULLSCREEN)
        {
            ToggleFullscreen();
        }
        glfwTerminate();
    }

    void SetAPI(API api)
    {
        _api = api;
    }

    const API GetAPI() 
    {
        return _api;
    }

    GLFWwindow* GetWindowPointer() 
    {
        return _window;
    }

    void SetWindowPointer(GLFWwindow* window) 
    {
        _window = window;
    }

    void CreateGLFWWindow(const WindowedMode& windowedMode) 
    {
        if (windowedMode == WindowedMode::WINDOWED) 
        {
            _currentWindowWidth = _windowedWidth;
            _currentWindowHeight = _windowedHeight;
            _window = glfwCreateWindow(_windowedWidth, _windowedHeight, (BackEnd::_windowName + " (OpenGL)").c_str(), NULL, NULL);
            //glfwSetWindowPos(_window, (_currentWindowWidth / 2), (_currentWindowHeight / 2));
        }
        else if (windowedMode == WindowedMode::FULLSCREEN)
        {
            _currentWindowWidth = _fullscreenWidth;
            _currentWindowHeight = _fullscreenHeight;
            _window = glfwCreateWindow(_fullscreenWidth, _fullscreenHeight, (BackEnd::_windowName + " (OpenGL)").c_str(), _monitor, NULL);
            //glfwSetWindowPos(_window, (_fullscreenWidth / 2), (_fullscreenHeight / 2));
        }
        _windowedMode = windowedMode;

        _windowPositionX = (_fullscreenWidth - _windowedWidth) / 2;
        _windowPositionY = (_fullscreenHeight - _windowedHeight) / 2;

        glfwSetWindowPos(_window, _windowPositionX, _windowPositionY);

        GLFWimage _windowIcon = LoadWindowIcon("res/icons/darkopsicon.png");

        if (_windowIcon.pixels)
        {
            glfwSetWindowIcon(_window, 1, &_windowIcon);
            // Free the image after setting the icon
            stbi_image_free(_windowIcon.pixels);
        }
    }

    void SetWindowedMode(const WindowedMode& windowedMode)
    {
        if (windowedMode == WindowedMode::WINDOWED) 
        {
            _currentWindowWidth = _windowedWidth;
            _currentWindowHeight = _windowedHeight;
            glfwSetWindowMonitor(_window, nullptr, 0, 0, _windowedWidth, _windowedHeight, _mode->refreshRate);
            glfwSetWindowPos(_window, _windowPositionX, _windowPositionY);
        }
        else if (windowedMode == WindowedMode::FULLSCREEN) 
        {
            _currentWindowWidth = _fullscreenWidth;
            _currentWindowHeight = _fullscreenHeight;
            glfwSetWindowMonitor(_window, _monitor, 0, 0, _fullscreenWidth, _fullscreenHeight, _mode->refreshRate);
        }
        _windowedMode = windowedMode;
    }

    void ToggleFullscreen() 
    {
        if (_windowedMode == WindowedMode::WINDOWED)
        {
            SetWindowedMode(WindowedMode::FULLSCREEN);
        }
        else 
        {
            SetWindowedMode(WindowedMode::WINDOWED);
        }
        if (GetAPI() == API::OPENGL)
        {
            //OpenGLBackEnd::HandleFrameBufferResized();
        }
        else 
        {
            VulkanBackEnd::HandleFrameBufferResized();
        }
    }

    void ForceCloseWindow()
    {
        _forceCloseWindow = true;
    }

    bool WindowHasFocus()
    {
        return _windowHasFocus;
    }

    bool WindowHasNotBeenForceClosed() 
    {
        return !_forceCloseWindow;
    }

    int GetWindowedWidth() 
    {
        return _windowedWidth;
    }

    int GetWindowedHeight() 
    {
        return _windowedHeight;
    }

    int GetFullScreenWidth()
    {
        return _fullscreenWidth;
    }

    int GetFullScreenHeight() 
    {
        return _fullscreenHeight;
    }

    int GetCurrentWindowWidth() 
    {
        return _currentWindowWidth;
    }

    int GetCurrentWindowHeight() 
    {
        return _currentWindowHeight;
    }

    bool WindowIsOpen() 
    {
        return !(glfwWindowShouldClose(_window) || _forceCloseWindow);
    }

    bool WindowIsMinimized()
    {
        int width = 0;
        int height = 0;
        glfwGetFramebufferSize(_window, &width, &height);
        return (width == 0 || height == 0);
    }

    const WindowedMode& GetWindowMode() 
    {
        return _windowedMode;
    }

    // Render Targets
    void SetPresentTargetSize(int width, int height)
    {
        _presentTargetWidth = width;
        _presentTargetHeight = height;
        if (GetAPI() == API::OPENGL)
        {
            //OpenGLBackEnd::SetPresentTargetSize(width, height);
        }
        else
        {
            //VulkanBackEnd::SetPresentTargetSize(width, height);
        }
    }

    int GetPresentTargetWidth() 
    {
        return _presentTargetWidth;
    }

    int GetPresentTargetHeight() 
    {
        return _presentTargetHeight;
    }

    // Callbacks
    void framebuffer_size_callback(GLFWwindow* /*window*/, int width, int height)
    {
        if (GetAPI() == API::OPENGL)
        {
        }
        else 
        {
            VulkanBackEnd::MarkFrameBufferAsResized();
        }
    }

    void window_focus_callback(GLFWwindow* /*window*/, int focused) 
    {
        if (focused) 
        {
            BackEnd::_windowHasFocus = true;
        }
        else 
        {
            BackEnd::_windowHasFocus = false;
        }
    }
}
