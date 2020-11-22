#pragma once


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

    EventObject(T* Object, ObjectFunction Function)
    {
        m_Object = Object;
        m_Function = Function;
    }

    virtual bool IsValid() const override
    {
        return static_cast<bool>(m_Object) && static_cast<bool>(m_Function);
    }

    virtual void Invoke(Args ... args) override
    {
        (m_Object->*m_Function)(args...);
    }

    virtual bool Compare(const EventObjectBase<Args ...>& Other) const override
    {
        if (EventObject<T, Args ...>* CastedOther = (EventObject<T, Args ...>*)(&Other))
        {
            return this->m_Object == CastedOther->m_Object && this->m_Function == CastedOther->m_Function;
        }

        return false;
    }

    virtual bool CompareObjectOnly(const EventObjectBase<Args ...>& Other) const override
    {
        if (EventObject<T, Args ...>* CastedOther = (EventObject<T, Args ...>*)(&Other))
        {
            return this->m_Object == CastedOther->m_Object;
        }

        return false;
    }

private:

    T* m_Object;
    ObjectFunction m_Function;
};

}