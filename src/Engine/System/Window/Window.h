#pragma once

#include "src/Engine/CarrotCore.h"

namespace Carrot
{

struct WindowData
{
    int32_t width;
    int32_t height;
    std::string title;
};

PTR(Window);

class Window : public Object
{
public:

    Window(const WindowData& wData);

    static WindowPtr CreateWindow(const WindowData& wData);


protected:

    virtual void InitializeWindow(){};

private:

    WindowData m_data;
};

}