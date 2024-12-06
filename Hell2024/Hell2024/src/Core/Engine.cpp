#include "Engine.hpp"
#include "BackEnd/BackEnd.hpp"
#include "Core/AssetManager.hpp"
#include "Game/Game.hpp"
#include "Renderer/Renderer.hpp"
#include "Utils/ErrorHandling/LogErrors.hpp"
#include "LoadingScreen/InitialWindow.hpp"

void Engine::Run() 
{
    // TODO: Log all warnings in a txt file
    //BuildWarningLogger logger;
    //logger.monitorBuild("E:\\Hell2024\\Hell2024\\Hell2024.sln");

    std::cout << "Loading screen starting" << std::endl;

    InitLoadingScreen();

    while (!finishedLoading)
    {

    }

    std::cout << "Loading screen finished" << std::endl;

    BackEnd::Init(API::OPENGL);

    while (BackEnd::WindowIsOpen()) 
    {
        BackEnd::BeginFrame();
        BackEnd::UpdateSubSystems();
        // Load files from disk
        if (!AssetManager::LoadingComplete())
        {
            AssetManager::LoadNextItem();
            Renderer::RenderLoadingScreen();
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

