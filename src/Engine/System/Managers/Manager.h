#pragma once

#include "src/Engine/Macros/Macro.h"
#include "src/Engine/Core/Object.h"

namespace Carrot
{

PTR(Manager);

class Manager : public Object
{
public:

    virtual void Initialize() = 0;
    virtual void Update(float dt) = 0;
};

} 
