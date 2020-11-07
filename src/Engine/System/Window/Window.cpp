#include "Window.h"
#include "src/Engine/Config.h"
#include "Platform/Window_Linux.h"
#include "src/Engine/Macros/Private/MacroCrossPlatform.h"

namespace Carrot
{

Window::Window(const WindowData& wData)
    : m_data(wData)
{
    InitializeWindow();
}

WindowPtr Window::CreateWindow(const WindowData& wData)
{
    return CREATE_OBJECT_PLATFORM(Window, CURRENT_PLATFORM, wData);
    //return std::make_shared<Window>(wData);
}

}