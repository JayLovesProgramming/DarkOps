#pragma once

#include "Renderer/RendererUtil.hpp"
#include "Renderer/ImGui/F8Console.hpp"

class Cursor
{
public:
    static inline bool _isCursorHidden = true;

    static void Draw(std::vector<RenderItem2D>* renderItems, hell::ivec2 viewportCenter, hell::ivec2 presentSize)
    {
        if (!_isCursorHidden)
        {
            //glEnable(GL_DEPTH_TEST);
            renderItems->push_back(RendererUtil::CreateRenderItem2D("orange_cursor", viewportCenter, { PRESENT_WIDTH, PRESENT_HEIGHT }, Alignment::CURSOR_POS, WHITE, { 20, 20 }));
        }
        //std::cout << "Showing cursor" << _isCursorHidden << std::endl;
    }

    static void ShowCustomCursor()
    {
        _isCursorHidden = false;
    }

    static  void HideCustomCursor()
    {
        _isCursorHidden = true;
    }

    static void ResetCursorPosition()
    {
        //glfwSetCursorPos(BackEnd::GetWindowPointer(), 0, 0);
    }
};