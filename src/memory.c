#include "../include/memory.h"

/* /////////////////////////////////////////////////////////
 * Call to get the Memory usage callMemoryUsage.
 * Creates a Memory Status struct to call memory.
 * Check status of global memory.
 * Print Total Memory in use, Total physical/virtual memory 
 * and Free physcal/virtual memory.
*/ //////////////////////////////////////////////////////////

double getTotalMemory() {

    double totalRam;
    struct sysinfo info;

    if(sysinfo(&info) < 0) perror("sysinfo");

    totalRam = (double) info.totalram / (MEM_GB);

    return totalRam;
}

double getAvailableMemory() {

    double freeRam;
    struct sysinfo info;

    if(sysinfo(&info) < 0) perror("sysinfo");

    freeRam  = (double) info.freeram / (MEM_GB);

    return freeRam;
}

double getCurrentMemoryUsage() {

    double totalRam, freeRam, ramUsage;
    struct sysinfo info;

    if(sysinfo(&info) < 0) perror("sysinfo");

    totalRam = getTotalMemory();
    freeRam = getAvailableMemory();
    ramUsage = totalRam - freeRam;

    return ramUsage;
}

double getTotalDiskSpace() {

    double spaceAvailable, totalSpace, spaceUsed;
    struct statvfs stat;
    const char *path = "/root";

    if(statvfs(path, &stat) < 0) perror("sysStatvfs");

    totalSpace = (double)(stat.f_frsize * stat.f_blocks) / (MEM_GB);

    return totalSpace;
}

double getAvailableDiskSpace() {

    double spaceAvailable, totalSpace, spaceUsed;
    struct statvfs stat;
    const char *path = "/root";
    if(statvfs(path, &stat) < 0) perror("sysStatvfs");

    spaceAvailable = (double) (stat.f_bsize * stat.f_bavail) / (MEM_GB);

    return spaceAvailable;
}

double getCurrentDiskSpace() {

    double spaceAvailable, totalSpace, spaceUsed;
    struct statvfs stat;
    const char *path = "/root";

    if(statvfs(path, &stat) < 0) perror("sysStatvfs");

    totalSpace = (double)(stat.f_frsize * stat.f_blocks) / (MEM_GB);
    spaceAvailable = (double) (stat.f_bsize * stat.f_bavail) / (MEM_GB);
    spaceUsed = totalSpace - spaceAvailable;

    return spaceUsed;
}