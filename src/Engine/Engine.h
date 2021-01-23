#pragma once

#include <vector>
#include "src/Engine/System/Managers/Manager.h"
#include "src/Engine/System/Managers/EventsManager.h"
#include "src/Engine/System/Managers/UpdateManager.h"
#include "src/Engine/System/Managers/FileManager.h"

namespace Carrot
{

PTR(Manager);



#include "src/Engine/Core/Interfaces/Common/Update/IUpdateable.h"
#include "src/Engine/Core/Object.h"
class SomeTest 
    : public Object
    , public IUpdateable
{
public:
    virtual void Update(float dt) override;
};



/**
 * To run engine, call Initialize() and then Loop()
*/
class Engine
{
public:

    FORCE_INLINE static Engine* GetInstance() { return m_instance; }

    void Initialize();
    void Loop();

    template<class TManager>
    TManager* GetManager();
    void RegisterManager(const ManagerPtr& Manager);

    int32_t GetCurrentFPS() const { return m_CurrentFPS; }

private:

    void OnDestroy(EventType Type, SDL_QuitEvent Event);

    bool m_IsInitialized = false;
    static Engine* m_instance;

    bool m_IsRunning = false;

    int32_t m_CurrentFPS = 0;

    void InitializeManagers();

    template<class TManager>
    TManager* InitializeManager();

    std::vector<ManagerPtr> m_Managers;

    std::shared_ptr<SomeTest> m_TestObject;
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