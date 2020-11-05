#pragma once

#include "../../CarrotCore.h"

namespace Carrot
{

struct WindowData
{
    int32_t width;
    int32_t height;
    std::string title;
};

PTR(WindowBase);

class WindowBase : public Object
{
public:

    WindowBase(const WindowData& wData);

    static WindowBasePtr CreateWindow(const WindowData& wData);


protected:

    virtual void InitializeWindow() = 0;

private:

    WindowData m_data;
};

}