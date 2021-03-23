#include "FileManager.h"
#include "src/Engine/Includes/STLIncludes.h"

namespace Carrot
{

void FileManager::Initialize()
{
    Run(ThreadRunMode::Detach, ThreadCallMode::LoopCall);
}

void FileManager::Main_Loop()
{
    {
        std::lock_guard<std::mutex> lock(GetMutex());
        // Read from file async
        {
            auto It = m_AsyncReadData.begin();
            auto End = m_AsyncReadData.end();

            while (It != End)
            {
                ReadData& Data = (*It);
                
                Data.Delegate.Broadcast(true, ReadFromFileSync(Data.FileName));

                It = m_AsyncReadData.erase(It);
                End = m_AsyncReadData.end();
            }
        }

        // Write to file async
        {
            auto It = m_AsyncWriteData.begin();
            auto End = m_AsyncWriteData.end();

            while (It != End)
            {
                WriteData& Data = (*It);

                WriteToFileSync(Data.FileName, Data.Data, Data.WPolicy);
                Data.Delegate.Broadcast(true);
                
                It = m_AsyncWriteData.erase(It);
                End = m_AsyncWriteData.end();
            }
        }
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void FileManager::Update(float dt)
{
    
}
    
std::string FileManager::ReadFromFile(
    const std::string& FileName, 
    ExecutionPolicy ExPolicy,
    FileReadAsyncDelegate AsyncDelegate)
{
    switch (ExPolicy)
    {
    case ExecutionPolicy::Sync:
        return ReadFromFileSync(FileName);
    case ExecutionPolicy::Async:
        ReadFromFileAsync(FileName, AsyncDelegate);
        break;
    }
    
    return std::string();
}

void FileManager::WriteToFile(
    const std::string& FileName, 
    const std::string& Data, 
    ExecutionPolicy ExPolicy,
    FileWriteAsyncDelegate AsyncDelegate,
    WritePolicy WPolicy)
{
    switch (ExPolicy)
    {
    case ExecutionPolicy::Sync:
        WriteToFileSync(FileName, Data, WPolicy);
        break;
    case ExecutionPolicy::Async:
        WriteToFileAsync(FileName, Data, WPolicy, AsyncDelegate);
        break;
    }
}

std::string FileManager::ReadFromFileSync(const std::string& FileName)
{
    std::ifstream FileIn(FileName);
    bool IsSuccess = !FileIn.fail();
    if (!EnsureMsg(IsSuccess, "[FileManager] Failed to open file " + FileName))
    {
        return std::string();
    }

    std::stringstream buffer;
    buffer << FileIn.rdbuf();

    FileIn.close();

    return buffer.str();
}

void FileManager::ReadFromFileAsync(const std::string& FileName, FileReadAsyncDelegate AsyncDelegate)
{
    m_AsyncReadData.push_back(ReadData{AsyncDelegate, FileName});
}

void FileManager::WriteToFileSync(const std::string& FileName, const std::string& Data, WritePolicy WPolicy)
{
    std::ofstream FileOut;
    switch (WPolicy)
    {
    case WritePolicy::AddToTheEndOfFile:
        FileOut.open(FileName, std::ios::app);
        break;
    case WritePolicy::Default:
        FileOut.open(FileName);
        break;
    }

    bool IsSuccess = !FileOut.fail();
    if (!EnsureMsg(IsSuccess, "[FileManager] Failed to open file " + FileName))
    {
        return;
    }

    FileOut << Data;
    FileOut.close();
}

void FileManager::WriteToFileAsync(const std::string& FileName, const std::string& Data, WritePolicy WPolicy, FileWriteAsyncDelegate AsyncDelegate)
{
    std::lock_guard<std::mutex> lock(GetMutex());

    m_AsyncWriteData.push_back(WriteData{AsyncDelegate, FileName, Data, WPolicy});
}

}
