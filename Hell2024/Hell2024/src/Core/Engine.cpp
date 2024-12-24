#include "Engine.hpp"

#include "BackEnd/BackEnd.hpp"
#include "Core/AssetManager.hpp"
#include "Game/Game.hpp"
#include "Renderer/Renderer.hpp"
#include "LoadingScreen/InitialWindow.hpp"

void Engine::Run() 
{
    std::cout << "Loading screen starting" << "\n";

    InitLoadingScreen();

    while (!finishedLoading)
    {

    }

    std::cout << "Loading screen finished" << "\n";

    BackEnd::Init(API::OPENGL);

    while (BackEnd::WindowIsOpen()) 
    {
        BackEnd::BeginFrame();
        BackEnd::UpdateSubSystems();
        // Load files from disk
        if (!AssetManager::LoadingComplete())
        {
            AssetManager::LoadNextItem();
            //Renderer::RenderLoadingScreen();
        }
        // Create game
        else if (!Game::IsLoaded())
        {
            Game::Create();
            AssetManager::UploadVertexData(); // Edge case bug here
            AssetManager::UploadWeightedVertexData();
        }
        // The game
        else if (Game::IsLoaded() && AssetManager::LoadingComplete()) 
        {
            Game::Update();
            Renderer::RenderFrame();
        }
        BackEnd::EndFrame();
    }
    BackEnd::CleanUp();
}

