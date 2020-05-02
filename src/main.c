#include "cpu.c"
#include "memory.c"

int main() {
    int cpu = 0;
    int memory = 0;
    int disk = 0;
    int diskSpace = 0;

    cpu = getCpuInfo();
    memory = callMemoryUsage(); // RAM Usage
    disk = getLogicalDiskInfo();
    diskSpace = getDiskSpace();
    
    return 0;
}
