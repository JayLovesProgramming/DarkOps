#pragma once

#include "Types/VertexBuffer.hpp"

namespace RendererStorage 
{
    int CreateSkinnedVertexBuffer();
    VertexBuffer* GetSkinnedVertexBufferByIndex(int index);
}