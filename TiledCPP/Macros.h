#pragma once

#include <cstdio>
#include <cstdarg>
#include <cstdio>   

inline char* format_helper(const char* fmt, ...) 
{
    static char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    return buffer;
}

#define FTEXT(fmt, ...) format_helper(fmt, ##__VA_ARGS__)