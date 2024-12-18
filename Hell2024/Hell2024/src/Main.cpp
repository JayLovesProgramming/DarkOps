// This prevents accidentally selecting your integrated GPU
extern "C"
{
    __declspec(dllexport) unsigned __int32 AmdPowerXpressRequestHighPerformance = 0x1;
    __declspec(dllexport) unsigned __int32 NvOptimusEnablement = 0x1;
}

#include <iostream>
#include "Core/Engine.hpp"

int main() 
{
    std::cout << "[init] Main" << std::endl;
    Engine::Run();
}