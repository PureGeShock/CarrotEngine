#pragma once

#include <string>
#include <iostream>
#include "src/Engine/Macros/Public/Enum.h"

namespace Carrot
{

ENUM(LogType, uint8_t, 
    Info = 1, 
    Warning, 
    Error
);

class Log
{
public:

    static void DisplayLog(LogType Type, const std::string& Text, bool WriteToFile = true);
    static void ClearLogFile();

private:

    static void DisplayLog(const std::string& LogType, const std::string& Text, bool WriteToFile);
};

void CarrotLog(LogType Type, const std::string& Text, bool WriteToFile = true);

}
