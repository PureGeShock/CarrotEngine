#include "Log.h"
#include "src/Engine/Engine.h"
#include "src/Engine/System/Managers/FileManager.h"

namespace Carrot
{

void CLog(LogType Type, const std::string& Text)
{
    Log::DisplayLog(Type, Text);
}

void Log::DisplayLog(LogType Type, const std::string& Text)
{
    DisplayLog(Type._to_string(), Text);
}

void Log::DisplayLog(const std::string& LogType, const std::string& Text)
{
    std::string LogResult = "Log: |" + LogType + "| " + Text + "\n";

    std::cout << LogResult;

#if WRITE_LOGS_TO_LOGFILE
    if (Engine::GetInstance()->IsInitialized())
    {
        if (FileManager* FileMgr = Engine::GetInstance()->GetManager<FileManager>())
        {
            FileMgr->WriteToFile(
                std::string(PROJECT_NAME) + ".log", 
                LogResult, 
                ExecutionPolicy::Async, 
                FileWriteAsyncDelegate(),
                WritePolicy::AddToTheEndOfFile);
        }   
    }
#endif
}

}