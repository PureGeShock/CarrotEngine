#include "FileManager.h"
#include "src/Engine/Includes/STLIncludes.h"

namespace Carrot
{

void FileManager::Initialize()
{
    ReadFileTaskExecutor.RunTaskExecutor(ThreadRunMode::Detach, ThreadCallMode::LoopCall);
    ReadFileTaskExecutor.OnExecuteTask.AddListener(this, &FileManager::OnReadTaskExecute);

    WriteFileTaskExecutor.RunTaskExecutor(ThreadRunMode::Detach, ThreadCallMode::LoopCall);
    WriteFileTaskExecutor.OnExecuteTask.AddListener(this, &FileManager::OnWriteTaskExecute);
}

void FileManager::OnReadTaskExecute(ReadData& Data)
{
    Data.Delegate.Broadcast(true, ReadFromFileSync(Data.FileName));
}

void FileManager::OnWriteTaskExecute(WriteData& Data)
{
    WriteToFileSync(Data.FileName, Data.Data, Data.WPolicy);
    Data.Delegate.Broadcast(true);
}

void FileManager::Update(float dt)
{
    WriteFileTaskExecutor.UpdateData();
    ReadFileTaskExecutor.UpdateData();
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
    ReadFileTaskExecutor.AddData(ReadData{AsyncDelegate, FileName});
}

void FileManager::WriteToFileSync(const std::string& FileName, const std::string& Data, WritePolicy WPolicy)
{
    if (!EnsureMsg(!FileName.empty(), "[FileManager] FileName is empty"))
    {
        return;
    }

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
    if (!EnsureMsg(IsSuccess, "[FileManager] Failed to write to file " + FileName))
    {
        return;
    }

    FileOut << Data;
    FileOut.close();
}

void FileManager::WriteToFileAsync(const std::string& FileName, const std::string& Data, WritePolicy WPolicy, FileWriteAsyncDelegate AsyncDelegate)
{
    WriteFileTaskExecutor.AddData(WriteData{AsyncDelegate, FileName, Data, WPolicy});
}

}
