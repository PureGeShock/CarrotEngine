#include "Engine.h"
#include "System/LogSystem/Log.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace Carrot
{

std::shared_ptr<Engine> Engine::m_instance = std::make_shared<Engine>();

void Engine::Initialize()
{
    if (!EnsureMsg(!m_IsInitialized, "Attempt to initialize Engine again."))
    {
        return;
    }

    /* Initialize every system in Engine */
    
    InitializeManagers();

    m_IsInitialized = m_IsRunning = true;

    OnEngineInitialized();
}

void Engine::Loop()
{
    while (m_IsRunning)
    {
        static float dt = 0.016f;

        uint32_t TicksDelta = SDL_GetTicks() - m_TicksCount;
        dt = (SDL_GetTicks() - m_TicksCount) / 1000.0f;
        m_TicksCount = SDL_GetTicks();

        /*for (int i = 0; i < 1000000; i++)
        {
            float SomeValue = std::sqrt(std::fabs(std::cos(std::sin(500))));
            std::sqrt(std::fabs(std::cos(std::sin(SomeValue * i))));
        }*/

        for (auto&& Manager : m_Managers)
        {
            Manager->Update(dt);
        }
    }
}

void Engine::InitializeManagers()
{
    /* Updated first managers */
    InitializeManager<EventsManager>()
        ->OnQuitEvent.AddListener(this, &Engine::OnDestroy);
    InitializeManager<FileManager>();
    InitializeManager<FPSManager>();    

    /* Updated last managers */
    InitializeManager<UpdateManager>();
    InitializeManager<RenderSystem>();
}

void Engine::OnEngineInitialized()
{
    Log::ClearLogFile();
}

void Engine::OnDestroy(EventType Type, SDL_QuitEvent Event)
{
    for (auto&& Manager : m_Managers)
    {
        Manager->Deinitialize();
    }

    m_IsRunning = false;
}

}