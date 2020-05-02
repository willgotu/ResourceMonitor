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

int getLogicalDiskInfo() {
    
    wchar_t LogicalDrives[MAX_PATH] = {0};
    DWORD driveNames = GetLogicalDriveStringsW(MAX_PATH, LogicalDrives);
    
    if (driveNames == 0) {
        wprintf(L"Failed to get drive names %ld", GetLastError());
        return 1;
    }

    if (driveNames > 0 && driveNames <= MAX_PATH) {
    
        wchar_t *CurrentDrive = LogicalDrives;
        
        while(*CurrentDrive) {
            wprintf(L"%ls\n", CurrentDrive);

            CurrentDrive += wcslen(CurrentDrive) + 1;
        }
    }
    return 0;
}

int getDiskSpace() {

    unsigned __int64 freeCall,
                    total,
                    free;
    LPCWSTR pszDrive = NULL;
    pszDrive = L"C:\\";
    int diskSpace = GetDiskFreeSpaceExW(pszDrive, (PULARGE_INTEGER) &freeCall,
        (PULARGE_INTEGER) &total, (PULARGE_INTEGER) &free);

    if (diskSpace == 0) {

        wprintf(L"Failed to get free disk space %ld", GetLastError());
        return 1;
    }	

    wprintf(L"Total space: %I64u MB\n", total / (1024*1024));
    wprintf(L"Free space on drive: %I64u MB\n", free / (1024*1024));
    
    return 0;
}