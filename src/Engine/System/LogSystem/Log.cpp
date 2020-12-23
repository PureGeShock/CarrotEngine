#include "Log.h"

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
    std::cout << "\n" << "Log: |" << LogType << "| " << Text << "\n";
}

}