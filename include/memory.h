#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <stdbool.h>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>

#define MEM_GB 1000 * 1000 * 1000

/* Helper functions to get the RAM info */ 
double getTotalMemory();
double getAvailableMemory();
double getCurrentMemoryUsage();

/* Helper functions to get disk info */
double getTotalDiskSpace();
double getAvailableDiskSpace();
double getCurrentDiskSpace();

#endif /* MEMORY_H */