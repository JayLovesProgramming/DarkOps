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

}
