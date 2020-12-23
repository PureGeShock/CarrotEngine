#pragma once

#include "src/Engine/Config.h"
#include "src/Engine/Macros/Private/MacroSystemPrivate.h"
#include "src/Engine/System/LogSystem/Log.h"

#if CURRENT_PLATFORM == Linux
    #define FORCE_INLINE __inline
#else
    #define FORCE_INLINE __forceinline
#endif

#define NONCOPYABLE(Type) Type(const Type&)=delete; Type& operator=(const Type&)=delete

#define EnsureMsg(Condition, Msg) \
    [=]()-> bool \
    { \
        if (Condition) \
        { \
            return true; \
        } \
        else \
        { \
            Carrot::CLog(Carrot::LogType::Error, Msg); \
            DEBUG_BREAK; \
        } \
        return false; \
    }()
