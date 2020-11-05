#pragma once

#include "src/Engine/CarrotCore.h"
#include "src/Engine/System/Window/WindowBase.h"

namespace Carrot
{

PTR(Window_Linux);

class Window_Linux : public WindowBase
{
protected:

    virtual void InitializeWindow(){} 
};

}