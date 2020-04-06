#include <windows.h>
#include <wchar.h>
#include <stdio.h>
#include <stdbool.h>

/* /////////////////////////////////////////////////////////
 * Function to get cpu info: getCpuInfo.
 * Open registry key to CPU.
 * Query CPU frequency (speed).
*/ /////////////////////////////////////////////////////////

int getCpuInfo(){
    DWORD totalSize = MAX_PATH;
    DWORD mhz = MAX_PATH;
    HKEY key;

   long status = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
        L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &key);

    if (status != ERROR_SUCCESS) {

        wprintf(L"RegOpenKeyExW() failed %ld", GetLastError());
        return -1;
    }

    status = RegQueryValueExW(key, L"~MHz", NULL, NULL, (LPBYTE) &mhz, &totalSize);

    if (status != ERROR_SUCCESS) {

        wprintf(L"RegQueryValueExW() failed %ld", GetLastError());
        return -1;
    }

    wprintf(L"CPU speed: %lu MHz\n", mhz);

    status = RegCloseKey(key);

    if (status != ERROR_SUCCESS) {

        wprintf(L"Failed to close registry handle %ld", GetLastError());
        return -1;
    }
    
    return 0;
}