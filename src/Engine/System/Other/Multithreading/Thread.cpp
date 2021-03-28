#include "Thread.h"

namespace Carrot
{

Thread::Thread()
{

}

Thread::~Thread()
{
    Stop();
}

void Thread::Run(
    ThreadRunMode RunMode /*= ThreadRunMode::Detach*/, 
    ThreadCallMode CallMode /*= ThreadCallMode::SingleCall*/,
    int32_t _EveryFrameSleepTime /*= 100 MS */)
{
    InitializeThreadCallMode(CallMode);
    
    if (!EnsureMsg(m_thread && m_thread->joinable(), "Thread cannot be ran."))
    {
        return;
    }

    EveryFrameSleepTime = _EveryFrameSleepTime;

    RunMode == ThreadRunMode::Join 
            ? m_thread->join()
            : m_thread->detach();
}

void Thread::Stop()
{
    IsValid = false;
}

Thread::ThreadCallModeMethod Thread::GetThreadCallModeMethod(ThreadCallMode Mode) const 
{
    ThreadCallModeMethod Method = &Thread::Main_Impl;

    switch (Mode)
    {
    case ThreadCallMode::SingleCall: Method = &Thread::Main_Impl; break;
    case ThreadCallMode::LoopCall: Method = &Thread::Main_Loop_Impl; break;
    }

    return Method;
}

void Thread::InitializeThreadCallMode(ThreadCallMode Mode)
{
    m_thread = std::unique_ptr<std::thread>(new std::thread(GetThreadCallModeMethod(Mode), this));
}

void Thread::Main_Impl()
{
    if (IsValid)
    {
        Main();
    }
}

void Thread::Main_Loop_Impl()
{
    while (IsValid)
    {
        Main_Loop();
        std::this_thread::sleep_for(std::chrono::milliseconds(EveryFrameSleepTime));
    }
}

}