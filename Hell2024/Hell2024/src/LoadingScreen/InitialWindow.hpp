#pragma once

#include "HellCommon.hpp"

constexpr static auto loadingScreenWidth = 1024;
constexpr static auto loadingScreenHeight = 576;
static auto finishedLoading = false;

void CenterWindowOnScreen(GLFWwindow* loadingWindow)
{
	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
	if (videoMode)
	{
		int screenWidth = videoMode->width;
		int screenHeight = videoMode->height;

		int windowX = (screenWidth - loadingScreenWidth) / 2;
		int windowY = (screenHeight - loadingScreenHeight) / 2;

		glfwSetWindowPos(loadingWindow, windowX, windowY);
	}
}

void InitLoadingScreen()
{
	if (!glfwInit())
	{
		std::cerr << "Failed to init GLFW (loading screen)" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* loadingWindow = glfwCreateWindow(loadingScreenWidth, loadingScreenHeight, "Loading Test", NULL, NULL);
	if (!loadingWindow)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	CenterWindowOnScreen(loadingWindow);

	glfwMakeContextCurrent(loadingWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD\n";
		return;
	}

	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

	float loadingProgress = 0.0f;

	while (!glfwWindowShouldClose(loadingWindow) && !finishedLoading)
	{
		loadingProgress += 0.0001f;
		if (loadingProgress >= 1.0f) 
		{
			loadingProgress = 1.0f;
			break; // Loading complete
		}

		glfwSwapBuffers(loadingWindow);
		glfwPollEvents();
		std::cout << "Looping loading screen" << std::endl;
	}

	finishedLoading = true; // Fallback
	glfwDestroyWindow(loadingWindow);
	//glfwTerminate();
	std::cout << "Terminated loading screen" << std::endl;
	return;
}