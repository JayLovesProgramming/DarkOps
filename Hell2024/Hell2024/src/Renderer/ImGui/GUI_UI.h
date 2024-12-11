//#pragma once
//
//
//#define IMGUI_DEFINE_MATH_OPERATORS
//#include "imgui.h"
//#include "backends/imgui_impl_glfw.h"
//#include "backends/imgui_impl_opengl3.h"
//#include <GLFW/glfw3.h>
//
//#include "BackEnd/BackEnd.hpp"
//
//#include "imgui.cpp"
//
//#include <iostream>
//
//
//class HellImGui
//{
//public:
//	GLFWwindow* window = BackEnd::GetWindowPointer();
//
//	static  void Init(GLFWwindow* window)
//	{
//		// Init ImGui context 
//		//IMGUI_CHECKVERSION();
//		//ImGui::CreateContext();
//
//		//// Set ImGui style (optional)
//		//ImGui::StyleColorsDark();
//
//		//// Init platform and renderer bindings for ImGui
//		//ImGui_ImplGlfw_InitForOpenGL(window, true);
//		//ImGui_ImplOpenGL3_Init("#version 330");
//
//		std::cout << "[INIT] ImGui" << "\n";
//	}
//
//	static inline void drawImGui()
//	{
//		ImGui_ImplOpenGL3_NewFrame();
//		ImGui_ImplGlfw_NewFrame();
//		ImGui::NewFrame();
//
//		// Draw ImGui UI
//		ImGui::Begin("Example window");
//		ImGui::Text("Hello, ImGui!!");
//		ImGui::End();
//
//		// Render 
//		ImGui::Render();
//		glClear(GL_COLOR_BUFFER_BIT);
//		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//		// Swap buffers and poll events
//		//glfwSwapBuffers(window)
//		std::cout << "[DRAWING] ImGui" << "\n";
//	}
//
//	static inline void cleanupImGui()
//	{
//		ImGui_ImplOpenGL3_Shutdown();
//		ImGui_ImplGlfw_Shutdown();
//		ImGui::DestroyContext();
//		std::cout << "[CLEANUP] ImGui" << "\n";
//	}
//};
//
//
