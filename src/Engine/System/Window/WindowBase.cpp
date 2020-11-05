#include "WindowBase.h"

namespace Carrot
{

WindowBase::WindowBase(const WindowData& wData)
    : m_data(wData)
{
    InitializeWindow();
}

WindowBasePtr WindowBase::CreateWindow(const WindowData& wData)
{
    return std::make_shared<WindowBase>(wData);
}

}