#include "UpdateManager.h"

namespace Carrot
{

void UpdateManager::RegisterUpdatable(IUpdateable* Obj)
{
    if (!EnsureMsg(Obj, "[UpdateManager] Trying to register nullptr object"))
    {
        return;
    }

#if PROJECT_CONFIGURATION == Debug
    bool IsAlreadyUpdatable = std::count(m_UpdatableObjects.begin(), m_UpdatableObjects.end(), Obj) > 0;
    EnsureMsg(!IsAlreadyUpdatable, "[UpdateManager] Trying to add object which is already updatable");
#endif

    m_UpdatableObjects.push_back(Obj);
}

void UpdateManager::UnregisterUpdatable(IUpdateable* Obj)
{
    if (!EnsureMsg(Obj, "[UpdateManager] Trying to unregister nullptr object"))
    {
        return;
    }

    auto FountIt = std::find(m_UpdatableObjects.begin(), m_UpdatableObjects.end(), Obj);
    if (FountIt != m_UpdatableObjects.end())
    {
        m_UpdatableObjects.erase(FountIt);
    }
}

void UpdateManager::Update(float dt)
{
    int32_t UpdatablesCount = m_UpdatableObjects.size();
    for (int32_t i = 0; i < UpdatablesCount; i++)
    {
        if (IUpdateable* Updatable = m_UpdatableObjects[i])
        {
            Updatable->Update(dt);
        }
    }    
}

}