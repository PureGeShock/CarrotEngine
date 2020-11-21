#include <string>
#include <iostream>
#include "src/Engine/Macros/Macro.h"

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

    static void DisplayLog(LogType Type, const std::string& Text);

private:

    static void DisplayLog(const std::string& LogType, const std::string& Text);
};

void CLog(LogType Type, const std::string& Text);

}