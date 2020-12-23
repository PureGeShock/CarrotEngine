#pragma once

#include "src/Engine/Includes/STLIncludes.h"
#include "src/Engine/Core/Object.h"
#include "src/Engine/Macros/Macro.h"
#include "EventObject.h"

namespace Carrot
{

template<typename ... Args>    
class EventDelegate
{
    using CurrentCallback = std::function<void(Args ...)>;
    
public:

    FORCE_INLINE void AddListener(CurrentCallback Callback)
    {
        Listeners.push_back(Callback);
    }

    FORCE_INLINE void AddWeakListener(const ObjectPtr& Subscriber, CurrentCallback Callback)
    {
        if (!EnsureMsg(Subscriber, "[Delegate, Weak] cannot subscribe on nullptr object."))
        {
            return;
        }

        WeakListeners.push_back(std::make_pair(std::weak_ptr<Object>(Subscriber), Callback));
    }

    template<class T>
    FORCE_INLINE void AddListener(T* Subscriber, void (T::*Func)(Args ...))
    {
        if (!EnsureMsg(Subscriber, "[Delegate] cannot subscribe on nullptr object."))
        {
            return;
        }

#if PROJECT_CONFIGURATION == Debug
        auto EventObjectForCompare = std::make_shared<EventObject<T, Args ...>>(Subscriber, Func);
        auto FoundIt = std::find_if(ObjectsListeners.begin(), ObjectsListeners.end(),
            [&EventObjectForCompare](const std::shared_ptr<EventObjectBase<Args ...>>& EventObject)
            {
                return EventObject->Compare(*EventObjectForCompare.get());
            });
        EnsureMsg(FoundIt == ObjectsListeners.end(), "[Delegate] This function was already added to the delegate!");
#endif
            
        ObjectsListeners.push_back(std::make_shared<EventObject<T, Args ...>>(Subscriber, Func));
    }

    template<class T>
    void RemoveListener(T* Subscriber, void (T::*Func)(Args ...))
    {
        if (!Subscriber)
        {
            CLog(LogType::Error, "[Delegate] cannot remove listener for nullptr object.");
            return;
        }

        auto EventObjectForCompare = std::make_shared<EventObject<T, Args ...>>(Subscriber, Func);
        while (true)
        {
            auto FoundIt = std::find_if(ObjectsListeners.begin(), ObjectsListeners.end(),
                [&EventObjectForCompare](const std::shared_ptr<EventObjectBase<Args ...>>& EventObject)
                {
                    return EventObject->Compare(*EventObjectForCompare.get());
                });

            if (FoundIt == ObjectsListeners.end())
            {
                break;
            }

            ObjectsListeners.erase(FoundIt);
        };
    }

    template<class T>
    void RemoveAllListeners(T* Subscriber)
    {
        if (!Subscriber)
        {
            CLog(LogType::Error, "[Delegate] cannot remove listeners for nullptr object.");
            return;
        }

        auto EventObjectForCompare = std::make_shared<EventObject<T, Args ...>>(Subscriber, nullptr);
        while (true)
        {
            auto FoundIt = std::find_if(ObjectsListeners.begin(), ObjectsListeners.end(),
                [&EventObjectForCompare](const std::shared_ptr<EventObjectBase<Args ...>>& EventObject)
                {
                    return EventObject->CompareObjectOnly(*EventObjectForCompare.get());
                });

            if (FoundIt == ObjectsListeners.end())
            {
                break;
            }

            ObjectsListeners.erase(FoundIt);
        }
    }

    void RemoveAllListeners()
    {
        ObjectsListeners.clear();
        Listeners.clear();
    }

    void Broadcast(Args ... args);
    void BroadcastIfBound(Args ... args);

private:

    void BroadcastListeners(Args ... args);
    void BroadcastWeakListeners(Args ... args);
    void BroadcastObjectListeners(Args ... args);

private:

    std::vector<CurrentCallback> Listeners;
    std::vector<std::pair<std::weak_ptr<Object>, CurrentCallback>> WeakListeners;
    std::vector<std::shared_ptr<EventObjectBase<Args ...>>> ObjectsListeners;
};

template<typename ... Args>
void EventDelegate<Args ...>::Broadcast(Args ... args)
{
    BroadcastListeners(args...);
    BroadcastWeakListeners(args...);
    BroadcastObjectListeners(args...);
}

template<typename ... Args>
void EventDelegate<Args ...>::BroadcastIfBound(Args ... args)
{
    if (!Listeners.empty()) { BroadcastListeners(args...); }
    if (!WeakListeners.empty()) { BroadcastWeakListeners(args...); }
    if (!ObjectsListeners.empty()) { BroadcastObjectListeners(args...); }
}

template<typename ... Args>
void EventDelegate<Args ...>::BroadcastListeners(Args ... args)
{
    auto it = Listeners.begin();
    auto end = Listeners.end();

    while (it != end)
    {
        auto Listener = (*it);
        if (Listener)
        {
            Listener(args...);
            ++it;
        }
        else
        {
            it = Listeners.erase(it);
            end = Listeners.end();
        }        
    }
}

template<typename ... Args>
void EventDelegate<Args ...>::BroadcastWeakListeners(Args ... args)
{
    auto it = WeakListeners.begin();
    auto end = WeakListeners.end();

    while (it != end)
    {
        auto Listener = (*it);
        if (Listener.first.lock() && Listener.second)
        {
            Listener.second(args...);
            ++it;
        }
        else
        {
            it = WeakListeners.erase(it);
            end = WeakListeners.end();
        }        
    }
}

template<typename ... Args>
void EventDelegate<Args ...>::BroadcastObjectListeners(Args ... args)
{
    auto it = ObjectsListeners.begin();
    auto end = ObjectsListeners.end();

    while (it != end)
    {
        auto Listener = (*it);
        if (Listener->IsValid())
        {
            Listener->Invoke(args...);
            ++it;
        }
        else
        {
            it = ObjectsListeners.erase(it);
            end = ObjectsListeners.end();
        }
    }
}

}