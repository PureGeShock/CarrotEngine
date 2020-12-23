#pragma once

#include "src/Engine/System/Managers/Manager.h"
#include "src/Engine/Includes/STLIncludes.h"
#include "src/Engine/Core/Interfaces/Common/Update/IUpdateable.h"

namespace Carrot
{

PTR(UpdateManager);

/**
 * If you want your class to be updatable (tickable), you
 * have to inherit from IUpdatable, override method Update
 * and call RegisterUpdatable in your class
*/
class UpdateManager : public Manager
{
public:

    virtual void Initialize() override {}

    void RegisterUpdatable(IUpdateable* Upd);
    void UnregisterUpdatable(IUpdateable* Upd);

    virtual void Update(float dt);

private:

    std::vector<IUpdateable*> m_UpdatableObjects;
};

} 
