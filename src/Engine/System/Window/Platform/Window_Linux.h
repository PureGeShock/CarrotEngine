#pragma once

#include "src/Engine/CarrotCore.h"
#include "src/Engine/System/Window/Window.h"

namespace Carrot
{

PTR(Window_Linux);

class Window_Linux : public Window
{
public:

    Window_Linux(const WindowData& wData);
    
protected:

    virtual void InitializeWindow(){} 
};

}