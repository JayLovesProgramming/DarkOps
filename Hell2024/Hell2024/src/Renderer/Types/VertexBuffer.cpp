#include "VertexBuffer.hpp" 
#include "../../BackEnd/BackEnd.hpp"

void VertexBuffer::AllocateSpace(int vertexCount)
{
    if (BackEnd::GetAPI() == API::OPENGL) 
    {
        glVertexBuffer.AllocateSpace(vertexCount);
    }
    else if (BackEnd::GetAPI() == API::VULKAN)
    {
        //vkVertexBuffer.AllocateSpace(vertexCount);
    }
}