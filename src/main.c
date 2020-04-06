#include "cpu.c"
#include "memory.c"

int main() {
    int cpu = 0;
    int memory = 0;

    cpu = getCpuInfo();
    memory = callMemoryUsage();
    return 0;
}