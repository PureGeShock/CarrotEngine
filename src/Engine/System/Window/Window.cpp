#include "Window.h"
#include "src/Engine/Config.h"
#include "src/Engine/Macros/Private/MacroCrossPlatform.h"
#include INCLUDE_CLASS_PLATFORM(Window, CURRENT_PLATFORM)

namespace Carrot
{

Window::Window(const WindowData& wData)
    : m_wData(wData)
{
}

WindowPtr Window::CreateWindow(const WindowData& wData)
{
    WindowPtr CreatedWindow = CREATE_OBJECT_PLATFORM(Window, CURRENT_PLATFORM, wData);
    CreatedWindow->InitializeWindow();
    return CreatedWindow;
}

}