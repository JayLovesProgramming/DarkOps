#pragma once

#include "RendererCommon.hpp"

class RoundManager
{
public:
    static inline int currentRound = 3;

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
        //std::cout << "Drawing round: " << ("round" + std::to_string(currentRound)).c_str() << "\n";

        RenderItem2D rounds = {};
        if (currentRound == 1)
        {
            rounds = RendererUtil::CreateRenderItem2D(
                "round1",
                viewportCenter,
                roundCounterSize,
                Alignment::TOP_RIGHT,
                WHITE,
                { 75, 125 }
            );
        }
        else if (currentRound == 2)
        {
            rounds = RendererUtil::CreateRenderItem2D(
                "round2",
                viewportCenter,
                roundCounterSize,
                Alignment::TOP_RIGHT,
                WHITE,
                { 75, 125 }
            );
        }
        else if (currentRound == 3)
        {
            rounds = RendererUtil::CreateRenderItem2D(
                "round3",
                viewportCenter,
                roundCounterSize,
                Alignment::TOP_RIGHT,
                WHITE,
                { 75, 125 }
            );
        }
        else if (currentRound == 4)
        {
            rounds = RendererUtil::CreateRenderItem2D(
                "round4",
                viewportCenter,
                roundCounterSize,
                Alignment::TOP_RIGHT,
                WHITE,
                { 75, 125 }
            );
        }
        else if (currentRound == 5)
        {
            rounds = RendererUtil::CreateRenderItem2D(
                "round5",
                viewportCenter,
                roundCounterSize,
                Alignment::TOP_RIGHT,
                WHITE,
                { 75, 125 }
            );
        }

        renderItems->push_back(rounds);

        //std::cout << "Drawing round: " << ("round" + std::to_string(currentRound)).c_str() << "\n";
    }
};
