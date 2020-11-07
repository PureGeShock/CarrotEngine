#include "CommonPrivate.h"
#include <memory>

/** All cross-platform classes must have signature as below (e.g. Window_Linux) */
#define INHERIT_PUBLIC(ClassName, Platform) public COMBINE(className##_, Platform)

#define MAKE_SHARED(ClassName, ...) std::make_shared<ClassName>(__VA_ARGS__)
#define CREATE_OBJECT_PLATFORM(ClassName, Platform, ...) MAKE_SHARED(COMBINE(ClassName##_, Platform), __VA_ARGS__)

