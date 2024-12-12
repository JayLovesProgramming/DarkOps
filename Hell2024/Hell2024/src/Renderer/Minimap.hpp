#pragma once

#include "RendererUtil.hpp"

class Minimap
{
public:
	static inline hell::ivec2 roundCounterSize = { (1920), (1080) }; // Width and height of the image, can be used to stretch or shrink an image

	static inline hell::ivec2 storedMinimapViewportCenter = {};

	static inline bool MINIMAP_ENABLED = true; // This will be set to false and init func will be called in the pre-game loading screen
	constexpr static auto MINIMAP_SIZE = 200; // Original Size = 200

	static void EnableMinimap()
	{
		MINIMAP_ENABLED = true;
	}

	static void DisableMinimap()
	{
		MINIMAP_ENABLED = false;
	}

	static void DrawMinimapPlaceholder(std::vector<RenderItem2D>* renderItems, hell::ivec2 viewportCenter, hell::ivec2 presentSize)
	{
		renderItems->push_back(RendererUtil::CreateRenderItem2D("Minimap_Overlay", viewportCenter, roundCounterSize, Alignment::MINIMAP_CUSTOM_TEST, WHITE, hell::ivec2(MINIMAP_SIZE, MINIMAP_SIZE)));
	}

	static void DrawBackground(std::vector<RenderItem2D>* renderItems, hell::ivec2 viewportCenter, hell::ivec2 presentSize)
	{
		if (MINIMAP_ENABLED)
		{
			storedMinimapViewportCenter = viewportCenter;
			storedMinimapViewportCenter.x -= 20;
			// TODO: Fix bottom left alignment so it works with all split screens?
			renderItems->push_back(RendererUtil::CreateRenderItem2D("Minimap_Background", storedMinimapViewportCenter, roundCounterSize, Alignment::MINIMAP_CUSTOM_TEST, WHITE, hell::ivec2(MINIMAP_SIZE, MINIMAP_SIZE)));

			////std::cout << "Drawing Minimap Background 1: " << roundCounterSize.x << roundCounterSize.y << std::endl;
			//std::cout << "Drawing Minimap Background 2: " << storedMinimapViewportCenter.x << ", " << storedMinimapViewportCenter.y << std::endl;

			DrawMinimapPlaceholder(renderItems, storedMinimapViewportCenter, presentSize);
		}
	}

	static void DrawBlip(std::vector<RenderItem2D>* renderItems, hell::ivec2 viewportCenter, hell::ivec2 presentSize)
	{
		//renderItems->push_back(RendererUtil::CreateRenderItem2D("Minimap_Background", viewportCenter, roundCounterSize, Alignment::BOTTOM_LEFT));
		////std::cout << "Drawing Minimap Background 1: " << roundCounterSize.x << roundCounterSize.y << std::endl;
		//std::cout << "Drawing Minimap Background 2: " << viewportCenter.x << viewportCenter.y << std::endl;
	}
};

