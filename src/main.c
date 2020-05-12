#include "cpu.c"
#include "memory.c"

int main(int argc, const char* argv[]) {
    int cpu = 0;
    int memory = 0;
    int disk = 0;
    int diskSpace = 0;
    int cpuSpeed = 0;
    double cpuSpeedGHz = 0;

    cpu = getCpuInfo();
    memory = callMemoryUsage(); // RAM Usage
    // disk = getLogicalDiskInfo();
    diskSpace = getDiskSpace(argv[1]);

    while(1){
        cpuSpeed = getClockSpeed();
        cpuSpeedGHz = (double) cpuSpeed / 1000.0;
        printf("Clock speed: %i MHz | %.3f GHz\n", cpuSpeed, cpuSpeedGHz);
        sleep(1);
    }

    return 0;
}

// int main()
// {
//     while(1){
//         printf("Clock speed: %i MHz | %.3f GHz\n", getClockSpeed(), ((double)getClockSpeed())/1000.0);
//         sleep(1);
//     }
    
//     return 0;
// }