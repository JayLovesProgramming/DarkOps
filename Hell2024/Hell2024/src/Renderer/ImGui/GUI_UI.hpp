#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "Game/Game.hpp"
#include "Input/Input.hpp"

 struct UIElements
{
	constexpr static int uiSpacing = 70;
	int positions[5];

	UIElements()
	{
		positions[0] = 0; // Fuck off
		positions[1] = 10;
		positions[2] = positions[1] + uiSpacing;
		positions[3] = positions[2] + uiSpacing;
		positions[4] = positions[3] + uiSpacing;
	}
};

namespace IMGUI
{
	//UIElements uiElements;

	static bool ImGui_DEBUG = true;
	static bool ImGui_DEMO = false;
	static bool F8_TOGGLED = false;

	static bool OVERLAYS_SHOW_FPS = false;
	static bool OVERLAYS_SHOW_DELTA_TIME = false;
	static bool OVERLAYS_SHOW_MEMORY_USAGE = false;
	static bool OVERLAYS_SHOW_BOUNDING_BOXES = false;
	static bool OVERLAYS_SHOW_COLLISION_DEBUG = false;
	static bool OVERLAYS_WIREFRAME_MODE = false;
	static bool OVERLAYS_SHOW_MINIMAP = false;

	static int MainBarHeight = 18;

	static std::vector<std::string> commandHistory;
	static std::string commandBuffer;

	void Init(GLFWwindow* window);

	void StartFrame();

	void RenderFrame();

	void ToggleDebugConsole();

	void DrawDemoWindow();

	void DrawMainBar();

	void DrawF8Command();

	void MainLoop();

	void Destroy();

	void AddToConsoleLog(std::string param);
	void ClearAllConsoleLogs();
	void ExecuteCommand(const char* command);

	bool IsAnyWindowOpen();

	// Overlays
	void DrawAllOverlays();

	void DrawFPS();
	void DrawDeltaTime();
	void DrawMinimap();

	int GetUIOverlayPosition(std::string type);

}
