#include "Engine.h"
#include "BackEnd/BackEnd.h"
#include "Core/AssetManager.h"
#include "Game/Game.h"
#include "Renderer/Renderer.h"
#include "Utils/ErrorHandling/LogErrors.h"

void Engine::Run() 
{
    // TODO: Log all warnings in a txt file
    //BuildWarningLogger logger;
    //logger.monitorBuild("E:\\Hell2024\\Hell2024\\Hell2024.sln");

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
        else 
        {
            Game::Update();
            Renderer::RenderFrame();
        }
        BackEnd::EndFrame();
    }
    BackEnd::CleanUp();
}

