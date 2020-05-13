#ifndef MEMORY_H
#define MEMORY_H

/* Helper functions to get the RAM info */ 
double getTotalMemory();
double getAvailableMemory();
double getCurrentMemoryUsage();

/* Helper functions to get disk info */
double getTotalDiskSpace();
double getAvailableDiskSpace();
double getCurrentDiskSpace();

#endif // MEMORY_H