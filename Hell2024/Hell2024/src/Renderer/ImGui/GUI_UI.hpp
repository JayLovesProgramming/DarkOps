#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "Game/Game.hpp"
#include "Input/Input.hpp"

namespace IMGUI
{
	static bool ImGui_DEBUG = true;
	static bool ImGui_DEMO = false;
	static bool ImGui_ShowDrawConsole;

	static bool OVERLAYS_SHOW_FPS = false;
	static bool OVERLAYS_SHOW_FRAME_TIME = false;
	static bool OVERLAYS_SHOW_MEMORY_USAGE = false;
	static bool OVERLAYS_SHOW_BOUNDING_BOXES = false;
	static bool OVERLAYS_SHOW_COLLISION_DEBUG = false;
	static bool OVERLAYS_WIREFRAME_MODE = false;
	static bool OVERLAYS_SHOW_MINIMAP = false;

	static int MainBarHeight = 18;

	static std::vector<std::string> commandHistory;
	static std::string commandBuffer;

	void ImGui_Init(GLFWwindow* window);

	void ImGui_StartFrame();

	void ImGui_RenderFrame();

	void ImGui_ToggleDebugConsole();

	void ImGui_DrawDemoWindow();

	void ImGui_DrawMainBar();

	void ImGui_DrawMainCommandBox();

	void ImGui_MainLoop();

	void ImGui_Destroy();

	void ImGui_AddToConsoleLog(std::string param);

	void ImGui_ClearAllConsoleLogs();

	void ImGui_ExecuteCommand(const char* command);

	void ImGui_DrawFPS(std::vector<RenderItem2D> *renderItems, hell::ivec2 debugTextLocation, hell::ivec2 presentSize);

	bool ImGui_IsAnyWindowOpen();
}
