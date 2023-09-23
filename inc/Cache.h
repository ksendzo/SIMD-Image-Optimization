#ifndef CACHE_H
#define CACHE_H

#include <stdlib.h>
#include <windows.h>

class Cache
{
public:
    static size_t cacheLine;
    static size_t cacheSize;
    static size_t cacheAssociativity;

    static void cache_info() {
        size_t line_size = 0;
        DWORD buffer_size = 0;
        DWORD i = 0;
        SYSTEM_LOGICAL_PROCESSOR_INFORMATION* buffer = 0;

        GetLogicalProcessorInformation(0, &buffer_size);
        buffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION*)malloc(buffer_size);
        GetLogicalProcessorInformation(&buffer[0], &buffer_size);

        for (i = 0; i != buffer_size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); ++i) {
            if (buffer[i].Relationship == RelationCache && buffer[i].Cache.Level == 1) {
                cacheLine = buffer[i].Cache.LineSize;
                cacheSize = buffer[i].Cache.Size;
                cacheAssociativity = buffer[i].Cache.Associativity;
                break;
            }
        }

        free(buffer);
    }
};

#endif