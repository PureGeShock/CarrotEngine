#pragma once

#include "src/Engine/System/Managers/Manager.h"
#include "src/Engine/Includes/STLIncludes.h"
#include "src/Engine/Includes/SDLIncludes.h"
#include "src/Engine/System/Other/Delegate/Delegate.h"

namespace Carrot
{

PTR(RenderSystem);

class RenderSystem : public Manager
{
public:

    virtual void Initialize() override;
    virtual void Deinitialize() override;
    virtual void Update(float dt) override;
};

} 
