#pragma once

#include "HellCommon.hpp"
#include "Core/AssetManager.hpp"

#include "stb_image.h"
#include "BackEnd/BackEnd.hpp"

enum class WindowPositions 
{
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT,
	CENTERED,
	BOTTOM_CENTERED,
	TOP_CENTERED
};

constexpr static auto loadingScreenWidth = 1024;
constexpr static auto loadingScreenHeight = 576;
constexpr static WindowPositions windowPosition = WindowPositions::CENTERED;

static bool finishedLoading = false;
static int windowX;
static int windowY;

GLuint LoadInitialWindowBackground(const char* filePath)
{
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	if (!data)
	{
		std::cerr << "Failed to load texture: " << filePath << std::endl;
		return 0;
	}

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);
	return textureID;
}

void DrawRoundedRectangle(float x, float y, float width, float height, float radius)
{
	int segments = 30; // Number of segments for the rounded corners
	float angleStep = 2.0f * HELL_PI / segments;

	// Top-left corner
	for (int i = 0; i < segments; ++i)
	{
		float angle = i * angleStep;
		float xOffset = cos(angle) * radius;
		float yOffset = sin(angle) * radius;

		glVertex2f(x + xOffset, y + height - radius + yOffset);  // top-left corner
	}

	// Repeat for other corners...
	// Render the background texture with rounded corners similarly
}

void DrawInitialWindowBackground(GLuint textureID)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, -1.0f); // Bottom-left
	glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, -1.0f);  // Bottom-right
	glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 1.0f);   // Top-right
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, 1.0f);  // Top-left
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	DrawRoundedRectangle(-1.0f, -1.0f, 1.0f, 1.0f, 0.1f);
}


void SetWindowPosition(GLFWwindow* loadingWindow)
{
	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

	if (!videoMode)
	{
		std::cout << "Initial window: Failed to find video mode" << std::endl;
		return;
	}

	int screenWidth = videoMode->width;
	int screenHeight = videoMode->height;

	switch (windowPosition)
	{
	case WindowPositions::CENTERED:
		windowX = (screenWidth - loadingScreenWidth) / 2;
		windowY = (screenHeight - loadingScreenHeight) / 2;
		break;

	case WindowPositions::TOP_LEFT:
		windowX = 0;
		windowY = 0;
		break;

	case WindowPositions::TOP_RIGHT:
		windowX = screenWidth - loadingScreenWidth;
		windowY = 0;
		break;

	case WindowPositions::BOTTOM_LEFT:
		windowX = 0;
		windowY = screenHeight - loadingScreenHeight;
		break;

	case WindowPositions::BOTTOM_RIGHT:
		windowX = screenWidth - loadingScreenWidth;
		windowY = screenHeight - loadingScreenHeight;
		break;

	case WindowPositions::BOTTOM_CENTERED:
		windowX = (screenWidth - loadingScreenWidth) / 2;
		windowY = screenHeight - loadingScreenHeight;
		break;

	case WindowPositions::TOP_CENTERED:
		windowX = (screenWidth - loadingScreenWidth) / 2;
		windowY = 0;
		break;

	default:
		std::cout << "Unknown window position" << std::endl;
		return;
	}

	glfwSetWindowPos(loadingWindow, windowX, windowY);
}

void InitLoadingScreen()
{
	if (!glfwInit())
	{
		std::cerr << "Failed to init GLFW (loading screen)" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_FALSE);

	GLFWwindow* loadingWindow = glfwCreateWindow(loadingScreenWidth, loadingScreenHeight, (BackEnd::_windowName + " (OpenGL)").c_str(), NULL, NULL);
	if (!loadingWindow)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	SetWindowPosition(loadingWindow);

	GLFWimage _windowIcon = BackEnd::LoadWindowIcon("E:/Hell2024Projects/Hell2024/Hell2024/Hell2024/res/icons/darkopsicon.png");
	if (_windowIcon.pixels)
	{
		glfwSetWindowIcon(loadingWindow, 1, &_windowIcon);
		// Free the image after setting the icon
		stbi_image_free(_windowIcon.pixels);
	};

	glfwMakeContextCurrent(loadingWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD/n";
		return;
	}

	glViewport(0, 0, loadingScreenWidth, loadingScreenHeight);

	GLuint backgroundImage = LoadInitialWindowBackground("E:/Hell2024Projects/Hell2024/Hell2024/Hell2024/res/icons/test.png");
	if (!backgroundImage)
	{
		std::cerr << "Failed to load background texture" << std::endl;
		return;
	}

	float loadingProgress = 0.0f;

	while (!glfwWindowShouldClose(loadingWindow) && !finishedLoading)
	{
		loadingProgress += 0.005f;
		if (loadingProgress >= 1.0f) 
		{
			loadingProgress = 1.0f;
			break; // Loading complete
		}

		glClear(GL_COLOR_BUFFER_BIT);

		DrawInitialWindowBackground(backgroundImage);

		glfwSwapBuffers(loadingWindow);
		glfwPollEvents();
		std::cout << "Loading progress: " << loadingProgress << std::endl;
	}

	finishedLoading = true; // Fallback

	glDeleteTextures(1, &backgroundImage);
	glfwDestroyWindow(loadingWindow);
	//glfwTerminate();


	std::cout << "Terminated loading screen" << std::endl;
	return;
}