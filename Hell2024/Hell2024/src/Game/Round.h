#pragma once

#include "Game/Player_RenderItems.h"

class RoundManager
{
public:
	inline static unsigned int currentRound = 2;
    inline static bool areAllDogsKilled = false;
    inline static bool areAllZombiesKilled = false;
    inline static int zombiesThisRound = 5;

    const inline static hell::ivec2 roundCounterSize = { 1920, 1080 };

	void increaseRound()
	{
		currentRound++;
	}

	void decreaseRound()
	{
		currentRound--;
	}

	unsigned int getCurrentRound()
	{
		return currentRound;
	}

	static void drawRounds(std::vector<RenderItem2D> *renderItems, hell::ivec2 viewportCenter)
    {
        unsigned int currentRound = RoundManager::currentRound;
        //std::cout << "Drawing round: " << currentRound << std::endl;

        if (currentRound == 1)
        {
            renderItems->push_back(RendererUtil::CreateRenderItem2D("round1", viewportCenter, roundCounterSize, Alignment::TOP_RIGHT));
        }
        else if (currentRound == 2)
        {
            renderItems->push_back(RendererUtil::CreateRenderItem2D("round2", viewportCenter, roundCounterSize, Alignment::TOP_RIGHT));
        }
        else if (currentRound == 3)
        {
            renderItems->push_back(RendererUtil::CreateRenderItem2D("round3", viewportCenter, roundCounterSize, Alignment::TOP_RIGHT));
        }
        else if (currentRound == 4)
        {
            renderItems->push_back(RendererUtil::CreateRenderItem2D("round4", viewportCenter, roundCounterSize, Alignment::TOP_RIGHT));
        }
        else if (currentRound == 5)
        {
            renderItems->push_back(RendererUtil::CreateRenderItem2D("round5", viewportCenter, roundCounterSize, Alignment::TOP_RIGHT));
        }
        else if (currentRound == 6)
        {
            renderItems->push_back(RendererUtil::CreateRenderItem2D("round6", viewportCenter, roundCounterSize, Alignment::TOP_RIGHT));
        }
        else if (currentRound == 7)
        {
            renderItems->push_back(RendererUtil::CreateRenderItem2D("round7", viewportCenter, roundCounterSize, Alignment::TOP_RIGHT));
        }
        else if (currentRound == 8)
        {
            renderItems->push_back(RendererUtil::CreateRenderItem2D("round8", viewportCenter, roundCounterSize, Alignment::TOP_RIGHT));
        }
        else if (currentRound == 9)
        {
            renderItems->push_back(RendererUtil::CreateRenderItem2D("round9", viewportCenter, roundCounterSize, Alignment::TOP_RIGHT));
        }
        else if (currentRound == 10)
        {
            renderItems->push_back(RendererUtil::CreateRenderItem2D("round10", viewportCenter, roundCounterSize, Alignment::TOP_RIGHT));
        }
        else
        {
            renderItems->push_back(RendererUtil::CreateRenderItem2D("round1", viewportCenter, roundCounterSize, Alignment::TOP_RIGHT));
        }
    }
};