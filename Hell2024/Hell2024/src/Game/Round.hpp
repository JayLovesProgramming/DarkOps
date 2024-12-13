#pragma once

static inline int currentRound = 2;

const inline static hell::ivec2 roundCounterSize = { 1920, 1080 };

static void IncreaseRound()
{
    currentRound++;
}

static void DecreaseRound()
{
    currentRound--;
}

static int GetCurrentRound()
{
    return currentRound;
}

static void SetCurrentRound(int newRound)
{
    currentRound = newRound;
}

static void DrawRounds(std::vector<RenderItem2D>* renderItems, hell::ivec2 viewportCenter, hell::ivec2 presentSize)
{
    //renderItems->clear();
    std::string roundText = "round" + std::to_string(currentRound);

    renderItems->push_back(RendererUtil::CreateRenderItem2D(roundText.c_str(), viewportCenter, roundCounterSize, Alignment::TOP_RIGHT, WHITE, { 75, 125 }));

    //std::cout << "Drawing round: " << roundText.c_str() << "\n";
}