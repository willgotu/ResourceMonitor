#include "../include/memory.h"

/* ////////////////////////////////////////////////////////////////////////////////
 * This file contains helper functions that get the information on a Linux
 * system's RAM and disk space.
*/ ////////////////////////////////////////////////////////////////////////////////


//---------------------------------------------------------------------------------
// getTotalMemory(): get the total RAM allocated on the system
//
// output:           return totalRam
//---------------------------------------------------------------------------------

double getTotalMemory() {

    double totalRam;
    struct sysinfo info;

    if(sysinfo(&info) < 0) perror("sysinfo");

    totalRam = (double) info.totalram / (MEM_GB);

    return totalRam;
}


//---------------------------------------------------------------------------------
// getAvailableMemory(): get the available RAM allocated on the system
//
// output:               return freeRam
//---------------------------------------------------------------------------------

double getAvailableMemory() {

    double freeRam;
    struct sysinfo info;

    if(sysinfo(&info) < 0) perror("sysinfo");

    freeRam  = (double) info.freeram / (MEM_GB);

    return freeRam;
}


//---------------------------------------------------------------------------------
// getCurrentMemoryUsage(): get the current RAM allocated on the system
//
// output:                  return ramUsage
//---------------------------------------------------------------------------------
double getCurrentMemoryUsage() {

    double totalRam, freeRam, ramUsage;
    struct sysinfo info;

    if(sysinfo(&info) < 0) perror("sysinfo");

    totalRam = getTotalMemory();
    freeRam = getAvailableMemory();
    ramUsage = totalRam - freeRam;

    return ramUsage;
}


//---------------------------------------------------------------------------------
// getTotalDiskSpace(): get total disk spaceallocated on the system
//
// output:              return totalSpace
//---------------------------------------------------------------------------------

double getTotalDiskSpace() {

    double spaceAvailable, totalSpace, spaceUsed;
    struct statvfs stat;
    const char *path = "/root";

    if(statvfs(path, &stat) < 0) perror("sysStatvfs");

    totalSpace = (double)(stat.f_frsize * stat.f_blocks) / (MEM_GB);

    return totalSpace;
}


//---------------------------------------------------------------------------------
// getAvailableDiskSpace(): get free disk space available on the system
//
// output:                  return spaceAvailable
//---------------------------------------------------------------------------------

double getAvailableDiskSpace() {

    double spaceAvailable, totalSpace, spaceUsed;
    struct statvfs stat;
    const char *path = "/root";

    if(statvfs(path, &stat) < 0) perror("sysStatvfs");

    spaceAvailable = (double) (stat.f_bsize * stat.f_bavail) / (MEM_GB);

    return spaceAvailable;
}


//---------------------------------------------------------------------------------
// getCurrentDiskSpace(): get current disk space allocated on the system
//
// output:                return spaceUsed
//---------------------------------------------------------------------------------

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


//---------------------------------------------------------------------------------