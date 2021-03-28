#pragma once

#include "src/Engine/System/Managers/Manager.h"
#include "src/Engine/Includes/STLIncludes.h"
#include "src/Engine/Includes/SDLIncludes.h"
#include "src/Engine/System/Other/Delegate/Delegate.h"
#include "src/Engine/System/Other/Multithreading/Thread.h"
#include "src/Engine/System/Other/Multithreading/ThreadTaskExecutor.h"

namespace Carrot
{

PTR(FileManager);

enum class ExecutionPolicy
{
    Sync,
    Async
};

enum class WritePolicy
{
    Default,
    AddToTheEndOfFile
};

using FileReadAsyncDelegate = EventDelegate<bool, const std::string&>;
using FileWriteAsyncDelegate = EventDelegate<bool>;

class FileManager 
    : public Manager
{
public:
    virtual void Initialize() override;

    virtual void Update(float dt) override;

    std::string ReadFromFile(
        const std::string& FileName, 
        ExecutionPolicy ExPolicy = ExecutionPolicy::Sync,
        FileReadAsyncDelegate AsyncDelegate = FileReadAsyncDelegate());
    void WriteToFile(
        const std::string& FileName, 
        const std::string& Data, 
        ExecutionPolicy ExPolicy = ExecutionPolicy::Sync,
        FileWriteAsyncDelegate AsyncDelegate = FileWriteAsyncDelegate(),
        WritePolicy WrPolicy = WritePolicy::Default);

private:

    struct ReadData
    {
        FileReadAsyncDelegate Delegate;
        std::string FileName;
    };

    std::string ReadFromFileSync(const std::string& FileName);
    void ReadFromFileAsync(const std::string& FileName, FileReadAsyncDelegate AsyncDelegate);
    
    ThreadTaskExecutor<ReadData> ReadFileTaskExecutor;
    void OnReadTaskExecute(ReadData& Data);

    struct WriteData
    {
        FileWriteAsyncDelegate Delegate;
        std::string FileName;
        std::string Data;
        WritePolicy WPolicy;
    };

    void WriteToFileSync(const std::string& FileName, const std::string& Data, WritePolicy WPolicy);
    void WriteToFileAsync(const std::string& FileName, const std::string& Data, WritePolicy WPolicy, FileWriteAsyncDelegate AsyncDelegate);
    
    ThreadTaskExecutor<WriteData> WriteFileTaskExecutor;
    void OnWriteTaskExecute(WriteData& Data);
};

} 
