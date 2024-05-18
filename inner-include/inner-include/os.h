#pragma once
#if __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR
    #define CY_TARGET_IOS 1
    #endif
#endif