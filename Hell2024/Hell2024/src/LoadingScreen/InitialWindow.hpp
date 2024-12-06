#pragma once

#include "HellCommon.hpp"

constexpr static auto loadingScreenWidth = 1280;
constexpr static auto loadingScreenHeight = 720;
static auto finishedLoading = false;

// TODO: Draw a image for background
void drawCircle(float cx, float cy, float radius, int num_segments)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i < num_segments; ++i)
	{
		float theta = 2.0f * 3.14159f * float(i) / float(num_segments);
		float x = radius * cosf(theta);
		float y = radius * sinf(theta);
		glVertex2f(x + cx, y + cy);
	}
	glEnd();
}

// TODO: Draw a image for background
void drawLoadingAnimation(float angle) 
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw a rotating circle (loader)
	glPushMatrix();
	glTranslatef(loadingScreenWidth / 2, loadingScreenHeight / 2, 0); // Move to center of screen
	glRotatef(angle, 0.0f, 0.0f, 1.0f); // Rotate the circle

	glColor3f(1.0f, 0.0f, 0.0f); // Set color to red
	drawCircle(0.0f, 0.0f, 50.0f, 50); // Draw the circle

	glPopMatrix();

	// Optionally, draw a progress bar or text
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

	glfwMakeContextCurrent(loadingWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD\n";
		return;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	float angle = 0.0f;
	float loadingProgress = 0.0f;

	while (!glfwWindowShouldClose(loadingWindow) && !finishedLoading)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		// Update the animation
		angle += 1.0f; // Rotate by 1 degree per frame
		if (angle >= 360.0f) angle = 0.0f; // Reset angle after a full rotation
		// Draw loading animation
		drawLoadingAnimation(angle);

		// Simulate loading progress (you can replace this with real loading logic)
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