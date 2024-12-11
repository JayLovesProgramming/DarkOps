#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>


void InitTheFuckingImGui(GLFWwindow* window)
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

void DrawTheFuckingImGuiWindow()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	// Draw ImGui UI
	ImGui::Begin("Example window");
	ImGui::Text("Hello, ImGui!!");
	ImGui::End();
	// Render 
	ImGui::Render();
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	// Swap buffers and poll events
	glfwSwapBuffers(BackEnd::GetWindowPointer());
	std::cout << "[DRAWING] ImGui" << "\n";
}


void cleanupImGui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	std::cout << "[CLEANUP] ImGui" << "\n";
}

