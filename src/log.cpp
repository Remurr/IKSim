#include "log.h"

#include <cstdio>
#include <cstdarg>

namespace
{
    void ErrorInternal(const char* format, va_list args)
    {
        vprintf(format, args);
    }
}

void Log::Print(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void Log::Debug(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void Log::Error(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    ErrorInternal(format, args);
    va_end(args);
}

bool ASRT(bool condition, const char* format, ...)
{
    if (condition == false)
    {
        va_list args;
        va_start(args, format);
        Log::Error(format, args);
        va_end(args);
    }
    return condition;
}

bool ASRT(bool condition)
{
    return ASRT(condition, "NoInfo");
}