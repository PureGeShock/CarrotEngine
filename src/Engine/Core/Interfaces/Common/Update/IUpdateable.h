#pragma once

#include "src/Engine/Core/Interfaces/Interface.h"
#include "src/Engine/Macros/Public/MacroSystem.h"

namespace Carrot
{

/**
 * This interface's purpose is to bring Update (Tick) functionality
 * in any object that inherits it
*/
class IUpdateable : public Interface
{
public:

    ~IUpdateable();

    virtual void Update(float dt) = 0;

    /** If pass true, the object's Update method will be called every tick */
    void SetUpdateActive(bool IsActive);
    FORCE_INLINE bool IsUpdateActive() const { return m_IsActive; }

private:

    bool m_IsActive = false;
};

}
