#include "CommonPrivate.h"

/** All cross-platform classes must have signature as below (e.g. Window_Linux) */
#define INHERIT_PUBLIC(className, Platform) public COMBINE(className##_, Platform)