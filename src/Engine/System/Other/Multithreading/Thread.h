#pragma once

#include "src/Engine/Includes/STLIncludes.h"
#include "src/Engine/Macros/Macro.h"

namespace Carrot
{

enum class ThreadCallMode
{
    None = 0,
    SingleCall,
    LoopCall
};

enum class ThreadRunMode
{
    None = 0,
    Join,
    Detach
};

/**
 * 
*/
class Thread
{
    /** Thread cannot be copied */
    NONCOPYABLE(Thread);

public:

    Thread();
    virtual ~Thread();

    /** Runs this thread */
    void Run(
        ThreadRunMode RunMode = ThreadRunMode::Detach, 
        ThreadCallMode CallMode = ThreadCallMode::SingleCall,
        int32_t EveryFrameSleepTime = 100 /* MS */);

    /** Stops this thread */
    void Stop();

protected:

    /** 
     * Dont call it manually, just override. To run thread, call Run().
     */
    virtual void Main() {};
    virtual void Main_Loop() {};
    //FORCE_INLINE std::mutex& GetMutex() { return m_mtx; };

private:

    bool IsValid = true;

    using ThreadCallModeMethod = void (Thread::*)();
    ThreadCallModeMethod GetThreadCallModeMethod(ThreadCallMode Mode) const;

    void InitializeThreadCallMode(ThreadCallMode Mode);

    /** NVI */
    void Main_Impl();
    void Main_Loop_Impl();

    std::unique_ptr<std::thread> m_thread;
    //std::mutex m_mtx;

    int32_t EveryFrameSleepTime = 0;
};

}
