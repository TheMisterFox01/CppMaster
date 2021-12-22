#pragma once

#include <cstdlib>

using byte = unsigned char;

class MemoryHeapStrategy
{
public:

    byte* alloc(size_t Amount)
    {
        return (byte*)malloc(Amount);
    }

    void dealloc(byte* Data)
    {
        free(Data);
    }
};