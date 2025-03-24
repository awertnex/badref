#pragma once

#include <defines.h>

#define LOG_WARN 1
#define LOG_INFO 1
#define LOG_DEBUG 1
#define LOG_TRACE 1

#if RELEASE == 1
#define LOG_DEBUG 1
#define LOG_TRACE 1
#endif

typedef enum LogLevel
{
    LOG_LEVEL_FATAL =   0,
    LOG_LEVEL_ERROR =   1,
    LOG_LEVEL_WARN =    2,
    LOG_LEVEL_INFO =    3,
    LOG_LEVEL_DEBUG =   4,
    LOG_LEVEL_TRACE =   5,
} LogLevel;

b8 init_logging();
void close_logging();
