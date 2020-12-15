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
    #define FORCE_INLINE __inline
#else
    #define FORCE_INLINE __forceinline
#endif

#define NONCOPYABLE(Type) Type(const Type&)=delete; Type& operator=(const Type&)=delete

#define EnsureMsg(Condition, Msg) Condition ? true : false

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


