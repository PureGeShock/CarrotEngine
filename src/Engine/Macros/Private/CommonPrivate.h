#pragma once

#define COMBINE(obj1, obj2)                     obj1##obj2
#define CONCAT(obj1, obj2)                      obj1 obj2
#define STRINGIFY(...)					        #__VA_ARGS__
#define SPLIT_SLASH(obj1, obj2)                 obj1/obj2
#define SPLIT_POINT_STR(obj1, obj2)             STRINGIFY(obj1.obj2)

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
