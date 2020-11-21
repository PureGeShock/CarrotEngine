#pragma once

#include <vector>
#include "src/Engine/System/Managers/Manager.h"

namespace Carrot
{

PTR(Manager);

/**
 * To run engine, call Initialize() and then Loop()
*/
class Engine
{
public:

    static Engine* GetInstance();
    void Initialize();

    template<class TManager>
    TManager* GetManager();
    void RegisterManager(const ManagerPtr& Manager);

private:

    bool m_IsInitialized = false;
    static Engine* m_instance;

    void InitializeManagers();

    void Loop();

    std::vector<ManagerPtr> m_managers;
};

template<class TManager>
TManager* Engine::GetManager()
{
    for (auto&& Manager : m_managers)
    {
        if (TManager* CastedManager = dynamic_cast<TManager*>(Manager.get()))
        {
            return CastedManager;
        }
    }

    return nullptr;
}

}