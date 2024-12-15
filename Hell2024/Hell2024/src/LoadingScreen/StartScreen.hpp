#pragma once

#include "Renderer/RendererUtil.hpp"

class StartScreen
{
public:
	static inline bool pressedStart = false;

	static void Init()
	{
	}

	static void Draw(std::vector<RenderItem2D>* renderItems, hell::ivec2 viewportCenter, hell::ivec2 presentSize)
	{
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
				Player* firstPlayer = Game::GetPlayerByIndex(0);
				firstPlayer->EnableControl();
				firstPlayer->SwitchWeapon("Knife", WeaponAction::DRAW_BEGIN);

				pressedStart = true;
			};
		}
	}

};

