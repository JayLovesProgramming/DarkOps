#pragma once

#include "Renderer/RendererUtil.hpp"

namespace Cursor
{
    static bool _isCursorHidden = true;

    static void Draw(std::vector<RenderItem2D>* renderItems, hell::ivec2 viewportCenter, hell::ivec2 presentSize)
    {
        //if (!_isCursorHidden)
        {
            renderItems->push_back(RendererUtil::CreateRenderItem2D("orange_cursor", viewportCenter, {PRESENT_WIDTH, PRESENT_HEIGHT}, Alignment::CURSOR_POS, WHITE, {50, 50}));
        }
    }

    static void ShowCustomCursor()
    {
        _isCursorHidden = false;
    }

    static void HideCustomCursor()
    {
        _isCursorHidden = true;
    }

    static void ResetCursorPosition()
    {
        //glfwSetCursorPos(BackEnd::GetWindowPointer(), 0, 0);
    }
}