#define _POSIX_C_SOURCE 199309L
#define _GNU_SOURCE

#include <stdio.h>
#include <stdbool.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

/* /////////////////////////////////////////////////////////
 * Function to get cpu info: getCpuInfo.
 * Open registry key to CPU.
 * Query CPU frequency (speed).
*/
/////////////////////////////////////////////////////////

int getCpuInfo()
{
    // printf("This system has %d processors configured and "
    //         "%d processors available.\n",
    //         get_nprocs_conf(), get_nprocs());
    // return 0;
    FILE *cpuinfo = fopen("/proc/cpuinfo", "rb");
    char line[1024];
    int count = 0;
    while (fgets(line, 1024, cpuinfo) != NULL)
    {
        if(strstr(line, "processor") != NULL) {
            printf("\n");
            puts(line);
            count++;
        }
        if(strstr(line, "cpu MHz") != NULL) puts(line);
    }
    fclose(cpuinfo);
    return 0;
}

static inline
uint64_t getCycles(void)
{                              /* 1 tick = 64 clocks */
     unsigned a, d;
     asm volatile("rdtsc" : "=a" (a), "=d" (d));
     return ((uint64_t)a) | (((uint64_t)d) << 32);
}

static inline
uint32_t getMillisecondCounter(void)
{
    uint32_t millisecondCounter;
    struct timespec t;

    clock_gettime (CLOCK_PROCESS_CPUTIME_ID, &t);
    millisecondCounter = (uint32_t) (t.tv_sec * 1000 + t.tv_nsec / 1000000);

    return millisecondCounter;
}

static inline
int getClockSpeed(void)
{
    const uint64_t cycles = getCycles();
    const uint32_t millis = getMillisecondCounter();
    int lastResult = 0;

    for (;;)
    {
        int n = 1000000;
        while (--n > 0) {}

        const uint32_t millisElapsed = getMillisecondCounter() - millis;
        const uint64_t cyclesNow = getCycles();

        if (millisElapsed > 80)
        {
            const int newResult = (int) (((cyclesNow - cycles) / millisElapsed) / 1000);

            if (millisElapsed > 500 || (lastResult == newResult && newResult > 100))
                return newResult;

            lastResult = newResult;
        }
    }
}