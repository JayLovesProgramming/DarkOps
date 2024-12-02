// Prevent accidentally selecting integrated GPU
extern "C" {
    __declspec(dllexport) unsigned __int32 AmdPowerXpressRequestHighPerformance = 0x1;
    __declspec(dllexport) unsigned __int32 NvOptimusEnablement = 0x1;
}

#include "Core/Engine.hpp"
#include <iostream>

int main() 
{
    Engine::Run();
}