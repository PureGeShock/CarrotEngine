#include "Window_Linux.h"

#if CURRENT_PLATFORM == Linux

#include <SDL2/SDL.h>

namespace Carrot
{

Window_Linux::Window_Linux(const WindowData& wData)
    : Window(wData)
{
}

void Window_Linux::InitializeWindow()
{
    m_SDLWindow = SDL_CreateWindow(
        m_wData.title.c_str(), 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        m_wData.width, m_wData.height, 
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!m_SDLWindow)
    {
        CLog(LogType::Error, "Creating window failed!");
    }
}

}

#endif