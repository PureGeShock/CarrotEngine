#pragma once

#include "src/Engine/Config.h"

#if CURRENT_PLATFORM == Linux

#include "src/Engine/CarrotCore.h"
#include "src/Engine/System/Window/Window.h"

class SDL_Window;

namespace Carrot
{

PTR(Window_Linux);

class Window_Linux : public Window
{
public:

    Window_Linux(const WindowData& wData);

protected:

    virtual void InitializeWindow();

private:

    SDL_Window* m_SDLWindow;
};

}

#endif