#pragma once

#include "src/Engine/CarrotCore.h"
#include "WindowBase.h"
#include "Linux/Window_Linux.h"
#include "src/Engine/Macros/Private/MacroCrossPlatform.h"

namespace Carrot
{

PTR(Window);

class Window : INHERIT_PUBLIC(Window, CURRENT_PLATFORM)
{
    
};

}