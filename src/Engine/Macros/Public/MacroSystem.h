#pragma once

#include "src/Engine/Config.h"
#include "src/Engine/System/LogSystem/Log.h"

#if CURRENT_PLATFORM == Linux
    #if PROJECT_CONFIGURATION == Debug
        #define DEBUG_BREAK asm("int $3")
    #else
        #define DEBUG_BREAK 1
    #endif
#elif CURRENT_PLATFORM == Windows
    #if PROJECT_CONFIGURATION == Debug
        #define DEBUG_BREAK __debugbreak()
    #else
        #define DEBUG_BREAK 1
    #endif
#endif

#if CURRENT_PLATFORM == Linux
    #define FORCEINLINE __inline
#else
    #define FORCEINLINE __forceinline
#endif


/*
#define EnsureMsg(Condition, Msg) \
    if (!Condition) \
    { \
        CLog(LogType::Error, Msg); \
        DEBUG_BREAK; \
        return false; \
    } \
    return true;
    */


