#include "IUpdateable.h"
#include "src/Engine/System/Managers/UpdateManager.h"
#include "src/Engine/Engine.h"

namespace Carrot
{

IUpdateable::~IUpdateable()
{
    if (auto UpdateMgr = Engine::GetInstance()->GetManager<UpdateManager>())
    {
        if (IsUpdateActive())
        {
            UpdateMgr->UnregisterUpdatable(this);   
        }
    }
}

void IUpdateable::SetUpdateActive(bool IsActive)
{
    if (auto UpdateMgr = Engine::GetInstance()->GetManager<UpdateManager>())
    {
        IsActive 
            ? UpdateMgr->RegisterUpdatable(this)
            : UpdateMgr->UnregisterUpdatable(this);

        m_IsActive = IsActive;
    }
}

}
