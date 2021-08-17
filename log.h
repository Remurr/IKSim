#pragma once

class Log
{
public:    
    static void Print(const char* format, ...);    
    static void Debug(const char* format, ...);    
    static void Error(const char* format, ...);            
};

bool ASRT(bool condition);
bool ASRT(bool condition, const char* format, ...);
