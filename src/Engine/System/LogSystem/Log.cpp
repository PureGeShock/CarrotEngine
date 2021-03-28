#include "Log.h"
#include "src/Engine/Engine.h"
#include "src/Engine/System/Managers/FileManager.h"

namespace Carrot
{

void Log::ClearLogFile()
{
#if WRITE_LOGS_TO_LOGFILE
    if (Engine::GetInstance()->IsInitialized())
    {
        if (FileManager* FileMgr = Engine::GetInstance()->GetManager<FileManager>())
        {
            FileMgr->WriteToFile(
                std::string(PROJECT_NAME) + ".log", 
                {}, 
                ExecutionPolicy::Async,
                FileWriteAsyncDelegate(),
                WritePolicy::Default);
        }   
    }
#endif
}

void CLog(LogType Type, const std::string& Text, bool WriteToFile)
{
    Log::DisplayLog(Type, Text, WriteToFile);
}

void Log::DisplayLog(LogType Type, const std::string& Text, bool WriteToFile)
{
    DisplayLog(Type._to_string(), Text, WriteToFile);
}

void Log::DisplayLog(const std::string& LogType, const std::string& Text, bool WriteToFile)
{
    std::string LogResult = "Log: |" + LogType + "| " + Text + "\n";

    std::cout << LogResult;

#if WRITE_LOGS_TO_LOGFILE
    if (Engine::GetInstance()->IsInitialized() && WriteToFile)
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