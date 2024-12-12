#pragma once

class RoundManager
{
public:
	inline static unsigned int currentRound = 2;

    inline static bool areAllDogsKilled = false;
    inline static bool areAllZombiesKilled = false;
    inline static int zombiesThisRound = 5;

    const inline static hell::ivec2 roundCounterSize = { 1920, 1080 };

	static void IncreaseRound()
	{
		currentRound++;
	}

    static void DecreaseRound()
	{
		currentRound--;
	}

    static unsigned int GetCurrentRound()
	{
		return currentRound;
	}

    static void SetCurrentRound(unsigned int newRound)
    {
        currentRound = newRound;
    }

    static void DrawRounds(std::vector<RenderItem2D>* renderItems, hell::ivec2 viewportCenter, hell::ivec2 presentSize)
    {
        //renderItems->clear();
        std::string roundText = "round" + std::to_string(RoundManager::currentRound);

        renderItems->push_back(RendererUtil::CreateRenderItem2D(roundText.c_str(), viewportCenter, roundCounterSize, Alignment::TOP_RIGHT, WHITE, {75, 125}));

        //std::cout << "Drawing round: " << roundText.c_str() << "\n";
    }
};