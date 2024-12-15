#pragma once

#include "Renderer/RendererUtil.hpp"

class StartScreen
{
public:
	//static inline GLuint startScreenTexture = {};

	//static inline int loadingProgress = 0;

	static inline bool pressedStart = false;

	static void Init()
	{
	/*	startScreenTexture = Util::LoadImage("E:/DarkOpsProjects/Hell2024/Hell2024/Hell2024/res/icons/loading_screen.png");
		if (startScreenTexture == 0)
		{
			std::cerr << "Failed to load start screen texture" << std::endl;
			return;
		}*/
	}

	static void Draw(std::vector<RenderItem2D>* renderItems, hell::ivec2 viewportCenter, hell::ivec2 presentSize)
	{
		//std::cout << "Texture ID: " << startScreenTexture << std::endl;
		if (!pressedStart)
		{
			renderItems->push_back(RendererUtil::CreateRenderItem2D("loading_screen", viewportCenter, { 1920, 1080 }, Alignment::CENTERED, WHITE));

			for (int i = 0; i < Game::GetPlayerCount(); i++)
			{
				if (Game::GetPlayerByIndex(i)->HasControl())
				{
					Game::GetPlayerByIndex(i)->DisableControl();
				}
			}

			if (Input::KeyPressed(HELL_KEY_ENTER))
			{
				Game::GetPlayerByIndex(0)->EnableControl();
				pressedStart = true;
			}
		}
	}

};

