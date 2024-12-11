#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>

bool showWindow = true;
bool ImGui_DEBUG = true;
bool ImGui_DEMO = false;

static std::vector<std::string> commandHistory;
static std::string commandBuffer;

void ImGui_Init(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();

	std::cout << "[INIT] ImGui" << "\n";
	std::cout << "[INIT] ImGui" << "\n";
	std::cout << "[INIT] ImGui" << "\n";
	std::cout << "[INIT] ImGui" << "\n";
	std::cout << "[INIT] ImGui" << "\n";
	std::cout << "[INIT] ImGui" << "\n";
	std::cout << "[INIT] ImGui" << "\n";
}

void ImGui_StartFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGui_RenderFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGui_DrawDemoWindow()
{
	ImGui_StartFrame();

	// Draw ImGui UI
	if (!showWindow)
	{
		return;
	}

	ImGui::ShowDemoWindow(&showWindow);

	// Render 
	ImGui_RenderFrame();

	if (ImGui_DEBUG)
	{
		std::cout << "[DRAWING] ImGui" << "\n";
	}
}

void ImGui_Main_Command_Box()
{
	ImGui_StartFrame();

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y / 3));

	ImGui::Begin("Command Prompt");

	hell::ivec2 commandBoxPos = { (BackEnd::GetCurrentWindowWidth() / 2), (BackEnd::GetCurrentWindowHeight()) };

	if (ImGui::BeginChild("CommandHistory", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), true))
	{
		for (const auto& line : commandHistory)
		{
			ImGui::TextUnformatted(line.c_str());
		}
		if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
		{
			ImGui::SetScrollHereY(1.0f);
		}
	}
	ImGui::EndChild();

	ImGui::End();

	ImGui_RenderFrame();
}

void ImGui_MainLoop()
{
	if (ImGui_DEMO)
	{
		ImGui_DrawDemoWindow();
	}
	else
	{
		ImGui_Main_Command_Box();
	}
}


void ImGui_Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	std::cout << "[CLEANUP] ImGui" << "\n";
}
