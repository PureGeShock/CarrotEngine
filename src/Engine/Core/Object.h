#pragma once

#include "src/Engine/Macros/Macro.h"

namespace Carrot
{

PTR(Object);

class Object 
    : public std::enable_shared_from_this<Object>
{

};

}