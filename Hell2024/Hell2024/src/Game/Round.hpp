#pragma once

class RoundManager
{
public:
	inline static unsigned int currentRound = 1;
    inline static bool areAllDogsKilled = false;
    inline static bool areAllZombiesKilled = false;
    inline static int zombiesThisRound = 5;

    const inline static hell::ivec2 roundCounterSize = { 1920, 1080 };

	void IncreaseRound()
	{
		currentRound++;
	}

	void DecreaseRound()
	{
		currentRound--;
	}

	unsigned int GetCurrentRound()
	{
		return currentRound;
	}

	static void DrawRounds(std::vector<RenderItem2D> *renderItems, hell::ivec2 viewportCenter, hell::ivec2 presentSize)
    {
        unsigned int currentRound = RoundManager::currentRound;
        //std::cout << viewportCenter.x << ", " << viewportCenter.y << "\n";
        //std::cout << "Drawing round: " << currentRound << "\n";
        //std::cout << presentSize.x << ", " << presentSize.y << "\n";

        if (currentRound)
        {
            renderItems->push_back(RendererUtil::CreateRenderItem2D(("round" + std::to_string(currentRound)).c_str(), viewportCenter, roundCounterSize, Alignment::TOP_RIGHT));
        }
        else // Fallback
        {
            //renderItems->push_back(RendererUtil::CreateRenderItem2D("round1", viewportCenter, roundCounterSize, Alignment::TOP_RIGHT));
        }
    }
};