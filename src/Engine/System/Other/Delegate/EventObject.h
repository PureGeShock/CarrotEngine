#pragma once

#include "src/Engine/Core/Object.h"

namespace Carrot
{

template<typename ... Args>
class EventObjectBase
{
public:

    virtual ~EventObjectBase() {};

    virtual bool IsValid() const = 0;
    virtual void Invoke(Args ... args) = 0;
    virtual bool Compare(const EventObjectBase<Args ...>& Other) const = 0;
    virtual bool CompareObjectOnly(const EventObjectBase<Args ...>& Other) const = 0;
};

template<class T, typename ... Args>
class EventObject 
    : public EventObjectBase<Args ...>
{
    using ObjectFunction = void (T::*)(Args ...);

public:

    EventObject(T* _Object, ObjectFunction Function)
    {
        if (!EnsureMsg(_Object && Function, "Cannot subscribe to invalid objects"))
        {
            return;
        }

        auto* ObjectHolder = static_cast<Object*>(_Object);
        if (!EnsureMsg(ObjectHolder, "ObjectSubscriber is not of type Object"))
        {
            return;
        }

        m_WeakHolder = ObjectHolder->This();
        m_Object = _Object;
        m_Function = Function;
    }

    virtual bool IsValid() const override
    {
        return static_cast<bool>(m_WeakHolder.lock()) && static_cast<bool>(m_Object) && static_cast<bool>(m_Function);
    }

    virtual void Invoke(Args ... args) override
    {
        if (IsValid())
        {
            (m_Object->*m_Function)(args...);
        }
    }

    virtual bool Compare(const EventObjectBase<Args ...>& Other) const override
    {
        if (EventObject<T, Args ...>* CastedOther = (EventObject<T, Args ...>*)(&Other))
        {
            if (IsValid() && CastedOther->IsValid())
            {
                return m_Object == CastedOther->m_Object && m_Function == CastedOther->m_Function;
            }
        }

        return false;
    }

    virtual bool CompareObjectOnly(const EventObjectBase<Args ...>& Other) const override
    {
        if (EventObject<T, Args ...>* CastedOther = (EventObject<T, Args ...>*)(&Other))
        {
            if (IsValid() && CastedOther->IsValid())
            {
                return m_Object == CastedOther->m_Object;
            }
        }

        return false;
    }

private:

    T* m_Object = nullptr;
    std::weak_ptr<Object> m_WeakHolder;
    ObjectFunction m_Function = nullptr;
};

}