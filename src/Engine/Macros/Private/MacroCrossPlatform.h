#include "CommonPrivate.h"
#include <memory>

/** All cross-platform classes must have signature as below (e.g. Window_Linux) */
#define INHERIT_PUBLIC(ClassName, Platform) public COMBINE(className##_, Platform)

/** Creating of Platform-depended objects */
#define MAKE_SHARED(ClassName, ...) std::make_shared<ClassName>(__VA_ARGS__)
#define CREATE_OBJECT_PLATFORM(ClassName, Platform, ...) MAKE_SHARED(COMBINE(ClassName##_, Platform), __VA_ARGS__)

/** Including of Platform-depended files */
#define INCLUDE_CLASS_PLATFORM(ClassName, PlatformArg) SPLIT_POINT_STR(SPLIT_SLASH(Platform, COMBINE(ClassName##_, PlatformArg)), h)

