#include "Engine.h"
#include "System/LogSystem/Log.h"
#include <SDL2/SDL.h>

namespace Carrot
{

Engine* Engine::m_instance = new Engine();

void Engine::Initialize()
{
    if (m_IsInitialized)
    {
        CLog(LogType::Error, "Attempt to initialize Engine again.");
        return;
    }

    // RenderSystem Initialization
    // TODO: Create rendersystem for different OS

    // ----- Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        CLog(LogType::Error, "SDL could not initialize.");
        return;
    }

    // ----- SDL OpenGL settings
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);





    // ----- Clean up
    //SDL_GL_DeleteContext(glContext);
}

void Engine::Loop()
{
    bool quit = false;
    while (!quit)
    {
        SDL_Event windowEvent;
        while (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT)
            {
                quit = true;
                break;
            }
        }

        const clock_t begin_time = clock();
        static float dt = 0.0f;

        for (auto&& Manager : m_managers)
        {
            Manager->Update(dt);
        }

        dt = float(clock() - begin_time) / CLOCKS_PER_SEC;

        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        /*
            do drawing here
        */
        //SDL_GL_SwapWindow(window);
    }
}

void Engine::InitializeManagers()
{
    
}

}