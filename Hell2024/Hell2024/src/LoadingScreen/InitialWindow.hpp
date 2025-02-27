#pragma once
// FIX: Change something and we can only rebuild

#include "HellCommon.hpp"
#include "Core/AssetManager.hpp"
#include "BackEnd/BackEnd.hpp"

// GIF
struct GifData
{
	unsigned char* data;
	int width;
	int height;
	int frames;
	int* delays;
	unsigned char** frameData;
};

constexpr static auto loadingScreenWidth = 1024;
constexpr static auto loadingScreenHeight = 576;
static bool finishedLoading = false;
static int windowX;
static int windowY;
static int loadingThrobberType = 3;

static float gifScale = 1.2;

// Debug
constexpr static auto debugInitialWindow = false;
constexpr static bool quickLoad = true;
constexpr static auto loadingTime = quickLoad ? 0.02f : 0.0005f; // Load slower to clearly see the loading process
static auto loadingProgress = 0.0f;

// LOAD
GifData LoadGif(const char* filePath)
{
	GifData gifData = { nullptr };
	FILE* file = nullptr;
	errno_t err;

	err = fopen_s(&file, filePath, "rb");
	if (err != 0 || !file)
	{
		std::cerr << "Failed to open GIF file: " << filePath << "\n";
		return gifData;
	}

	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	unsigned char* buffer = new unsigned char[fileSize];
	fread(buffer, 1, fileSize, file);
	fclose(file);

	int* delays = nullptr;
	int x = 0, y = 0, z = 0, comp = 0;
	gifData.data = stbi_load_gif_from_memory(buffer, fileSize, &delays, &gifData.width, &gifData.height, &gifData.frames, &comp, 4);

	if (gifData.data) 
	{
		gifData.delays = delays;
		gifData.frameData = new unsigned char* [gifData.frames];
		int frameSize = gifData.width * gifData.height * 4;
		for (int i = 0; i < gifData.frames; ++i) 
		{
			gifData.frameData[i] = gifData.data + (i * frameSize);
		}
	}
	else 
	{
		std::cerr << "Failed to load GIF: " << filePath << "\n";
	}

	delete[] buffer;
	return gifData;
}


// DRAW
void DrawInitialWindowBackground(GLuint textureID, float loadingProgress)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	// Draw loading circle
	float centerX = 0.0f;
	float centerY = -0.8f;
	float radius = 0.1f;
	int segments = 60;

	glPushMatrix();
	glTranslatef(centerX, centerY, 0.0f);
	glRotatef(loadingProgress * 360.0f, 0.0f, 0.0f, 1.0f);

	glPopMatrix();
	// Reset color
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

// DRAW
void DrawGifFrame(const GifData& gifData, int frameIndex, float x, float y, float width, float height)
{
	if (frameIndex >= gifData.frames)
	{
		std::cerr << "Invalid frame index" << "\n";
		return;
	}

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Enable alpha blending for transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set texture parameters to support transparency
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, gifData.width, gifData.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, gifData.frameData[frameIndex]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// When drawing, use white color to preserve original image colors
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width, y);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width, y + height);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y + height);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glDeleteTextures(1, &textureID);
}



void InitLoadingScreen()
{
	if (!glfwInit())
	{
		std::cerr << "Failed to init GLFW (loading screen)" << "\n";
		return;
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_FALSE);

	GLFWwindow* loadingWindow = glfwCreateWindow(loadingScreenWidth, loadingScreenHeight, (BackEnd::_windowName + " (OpenGL)").c_str(), NULL, NULL);
	if (!loadingWindow)
	{
		std::cerr << "Failed to create GLFW window" << "\n";
		glfwTerminate();
		return;
	}

	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
	assert(videoMode);
	int screenWidth = videoMode->width;
	int screenHeight = videoMode->height;
	windowX = (screenWidth - loadingScreenWidth) / 2;
	windowY = (screenHeight - loadingScreenHeight) / 2;
	glfwSetWindowPos(loadingWindow, windowX, windowY);

	GLFWimage _windowIcon = BackEnd::LoadWindowIcon("res/icons/darkopsicon.png");
	if (_windowIcon.pixels)
	{
		glfwSetWindowIcon(loadingWindow, 1, &_windowIcon);
		// Free the image after setting the icon
		stbi_image_free(_windowIcon.pixels);
	};

	glfwMakeContextCurrent(loadingWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << "\n";
		return;
	}

	glViewport(0, 0, loadingScreenWidth, loadingScreenHeight);

	GLuint backgroundImage = Util::LoadImage("res/icons/test.png");
	if (!backgroundImage)
	{
		std::cerr << "Failed to load background texture" << "\n";
		return;
	}

    // Load the GIF
	GifData gifData = LoadGif(("res/icons/loading_throbber_" + std::to_string(loadingThrobberType) + ".gif").c_str());
    if (!gifData.data)
    {
        std::cerr << "Failed to load GIF" << "\n";
        return;
    }

	int currentFrame = 0;
	double lastFrameTime = glfwGetTime();


	while (!glfwWindowShouldClose(loadingWindow) && !finishedLoading)
	{
		loadingProgress += loadingTime;
		if (loadingProgress >= 1.0f) 
		{
			loadingProgress = 1.0f;
			break; // Loading complete
		}

		glClear(GL_COLOR_BUFFER_BIT);

		DrawInitialWindowBackground(backgroundImage, loadingProgress);

		// Update GIF frame
		double currentTime = glfwGetTime();
		if (currentTime - lastFrameTime > gifData.delays[currentFrame] / 1000.0)
		{
			currentFrame = (currentFrame + 1) % gifData.frames;
			lastFrameTime = currentTime;
		}

		if (debugInitialWindow)
		{
			//std::cout << "Loading progress: " << loadingProgress << "\n";
			//std::cout << gifData.width << ", " << gifData.height << "\n";
			std::cout << currentFrame << "\n";
		}

		DrawGifFrame(gifData, currentFrame, 0.85, -0.95, 0.1 * gifScale, 0.17 * gifScale);

		glfwSwapBuffers(loadingWindow);
		glfwPollEvents();
	}

	finishedLoading = true;
	stbi_image_free(gifData.data);
	delete[] gifData.delays;
	delete[] gifData.frameData;
	glDeleteTextures(1, &backgroundImage);
	glfwDestroyWindow(loadingWindow);
	//glfwTerminate();

	if (debugInitialWindow)
	{
		std::cout << "Terminated loading screen" << "\n";
	}
}