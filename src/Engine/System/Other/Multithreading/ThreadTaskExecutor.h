#pragma once

#include "src/Engine/CarrotCore.h"
#include "src/Engine/Includes/STLIncludes.h"
#include "src/Engine/System/Other/Multithreading/Thread.h"

namespace Carrot
{

/**
 * 
*/
template<typename TaskData>
class ThreadTaskExecutor : public Thread
{

public:

    virtual void RunTaskExecutor(
        ThreadRunMode RunMode = ThreadRunMode::Detach, 
        ThreadCallMode CallMode = ThreadCallMode::SingleCall,
        int32_t EveryFrameSleepTime = 100 /* MS */,
        int32_t SleepTimeWhileWaitingForData = 100 /* MS */);

    virtual void AddData(const TaskData& Data);
    /* Call in update method of the calling thread (e.g. in MainThread) */
    virtual void UpdateData();

    EventDelegate<TaskData&> OnExecuteTask;

protected:

    virtual void ExecuteTask(TaskData& Data);

    virtual void Main_Loop() override;

private:

    bool StartExecution = false;

    std::vector<TaskData> m_RemainingData;
    std::vector<TaskData> m_ActiveData;

    int32_t SleepTimeWhileWaitingForData = 0;
};

template<typename TaskData>
void ThreadTaskExecutor<TaskData>::RunTaskExecutor(
    ThreadRunMode RunMode, 
    ThreadCallMode CallMode,
    int32_t _EveryFrameSleepTime,
    int32_t _SleepTimeWhileWaitingForData)
{
    Run(RunMode, CallMode, _EveryFrameSleepTime);
    SleepTimeWhileWaitingForData = _SleepTimeWhileWaitingForData;
}
    
template<typename TaskData>
void ThreadTaskExecutor<TaskData>::ExecuteTask(TaskData& Data)
{
    OnExecuteTask.BroadcastIfBound(Data);
}

template<typename TaskData>
void ThreadTaskExecutor<TaskData>::Main_Loop()
{
    while (!StartExecution)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(SleepTimeWhileWaitingForData));
    }

    for (int32_t i = 0; i < m_ActiveData.size(); i++)
    {
        ExecuteTask(m_ActiveData[i]);
    }

    m_ActiveData.clear();

    StartExecution = false;
}

template<typename TaskData>
void ThreadTaskExecutor<TaskData>::AddData(const TaskData& Data)
{
    m_RemainingData.push_back(Data);
}

template<typename TaskData>
void ThreadTaskExecutor<TaskData>::UpdateData()
{
    if (!StartExecution)
    {
        if (!m_RemainingData.empty())
        {
            m_ActiveData = m_RemainingData;
            m_RemainingData.clear();
            StartExecution = true;
        }
    }
}

}
