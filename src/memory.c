#include <windows.h>
#include <wchar.h>
#include <stdio.h>
#include <stdbool.h>

/* /////////////////////////////////////////////////////////
 * Call to get the Memory usage callMemoryUsage.
 * Uses windows api.
 * Creates a Memory Status struct to call memory.
 * Check status of global memory.
 * Print Total Memory in use, Total physical/virtual memory 
 * and Free physcal/virtual memory.
*/ //////////////////////////////////////////////////////////

int callMemoryUsage() {
    MEMORYSTATUSEX memUsage = {0};

    memUsage.dwLength = sizeof(memUsage);

    bool isMemExist = GlobalMemoryStatusEx(&memUsage);

    if (isMemExist == 0) {
        wprintf(L"Failed to memory status %ld", GetLastError());
        return -1;
    }

    wprintf(L"Memory in use: %ld percent\n", memUsage.dwMemoryLoad);
    wprintf(L"Total physical memory: %lld bytes\n", memUsage.ullTotalPhys);
    wprintf(L"Free physical memory: %lld bytes\n", memUsage.ullAvailPhys);
    wprintf(L"Total virtual memory: %lld bytes\n", memUsage.ullTotalVirtual);
    wprintf(L"Free virtual memory: %lld bytes\n", memUsage.ullAvailVirtual);

    return 0;  
}