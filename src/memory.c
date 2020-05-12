#include <stdio.h>
#include <stdbool.h>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>

/* /////////////////////////////////////////////////////////
 * Call to get the Memory usage callMemoryUsage.
 * Uses windows api.
 * Creates a Memory Status struct to call memory.
 * Check status of global memory.
 * Print Total Memory in use, Total physical/virtual memory 
 * and Free physcal/virtual memory.
*/ //////////////////////////////////////////////////////////
#define MEM_GB 1024 * 1024 * 1024

int callMemoryUsage() {

    double totalRam, freeRam, ramUsage;
    struct sysinfo info;

    if(sysinfo(&info) < 0) perror("sysinfo");

    totalRam = (double) info.totalram / (MEM_GB);
    freeRam  = (double) info.freeram / (MEM_GB);
    ramUsage = totalRam - freeRam;

    printf("RAM available = %0.2f GB\
            Free RAM = %0.2f GB\
            Total RAM = %0.2f GB\n", ramUsage, freeRam, totalRam);

    return 0;
}

int getDiskSpace(const char* path) {

    double spaceAvailable, totalSpace, spaceUsed;
    struct statvfs stat;

    if(statvfs(path, &stat) < 0) perror("sysStatvfs");

    totalSpace = (double)(stat.f_frsize * stat.f_blocks) / (MEM_GB);
    spaceAvailable = (double) (stat.f_bsize * stat.f_bavail) / (MEM_GB);
    spaceUsed = totalSpace - spaceAvailable;

    printf("Total space = %0.2f GB\
            Available space = %0.2f GB\
            Currently used space = %0.2f GB\n", totalSpace, spaceAvailable, spaceUsed);

    return 0;
}