#pragma once

#include <vector>
#include "src/Engine/System/Managers/Manager.h"
#include "src/Engine/System/Managers/EventsManager.h"
#include "src/Engine/System/Managers/UpdateManager.h"
#include "src/Engine/System/Managers/FileManager.h"
#include "src/Engine/System/Managers/Performance/FPSManager.h"
#include "src/Engine/System/Managers/Rendering/RenderSystem.h"

namespace Carrot
{

PTR(Manager);

/**
 * To run engine, call Initialize() and then Loop()
*/
class Engine
    : public Object
{
public:

    FORCE_INLINE static std::shared_ptr<Engine> GetInstance() { return m_instance; }

    void Initialize();
    FORCE_INLINE bool IsInitialized() const { return m_IsInitialized; }
    void Loop();

    template<class TManager>
    TManager* GetManager();

private:

    void OnDestroy(EventType Type, SDL_QuitEvent Event);

    bool m_IsInitialized = false;
    static std::shared_ptr<Engine> m_instance;

    bool m_IsRunning = false;

    uint32_t m_TicksCount = 0;

    void InitializeManagers();

    template<class TManager>
    TManager* InitializeManager();

    void OnEngineInitialized();

    std::vector<ManagerPtr> m_Managers;
};

template<class TManager>
TManager* Engine::GetManager()
{
    for (auto&& Manager : m_Managers)
    {
        if (TManager* CastedManager = dynamic_cast<TManager*>(Manager.get()))
        {
            return CastedManager;
        }
    }

    EnsureMsg(false, "The manager you trying to retrieve doesn't exist");
    return nullptr;
}

template<class TManager>
TManager* Engine::InitializeManager()
{
    std::shared_ptr<TManager> NewManager = std::make_shared<TManager>();
    NewManager->Initialize();
    m_Managers.push_back(NewManager);

    return NewManager.get();
}

}