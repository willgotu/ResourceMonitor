#include "../include/cpu.h"

/* ////////////////////////////////////////////////////////////////////////////////
 * This file contains helper functions that help get the frequency of a CPU on a
 * Linux system.
*/ ////////////////////////////////////////////////////////////////////////////////


struct timespec t;

//---------------------------------------------------------------------------------
// getNumberOfProcessors(): call get_nprocs to get the numbers of processors 
//                          available on the system
//
// output:      return number of processors
//---------------------------------------------------------------------------------

int getNumberOfProcessors() {

    return get_nprocs();
}

//---------------------------------------------------------------------------------
// getCycles(): use the rdtsc (read time stamp counter) instruction to count the
//              number of cycles since a reset
//
// output:      return cycle count (return value stored in 64-bit MSR)
//---------------------------------------------------------------------------------

static inline uint64_t getCycles() {     

    /* 1 tick = 64 clocks */
    unsigned a, d;

    asm volatile("rdtsc" : "=a" (a), "=d" (d));

    return ((uint64_t)a) | (((uint64_t)d) << 32);
}


//---------------------------------------------------------------------------------
// getMillisecondCounter(): get the time in milliseconds
//
// output:                  return millisecondCounter
//---------------------------------------------------------------------------------

static inline uint32_t getMillisecondCounter() {

    uint32_t millisecondCounter;
    
    clock_gettime (CLOCK_PROCESS_CPUTIME_ID, &t);
    millisecondCounter = (uint32_t) (t.tv_sec * 1000 + t.tv_nsec / 1000000);

    return millisecondCounter;
}


//---------------------------------------------------------------------------------
// getClockSpeed(): get the clock speed of a CPU by taking the the cycles and time
//                  taken by system
//
// output:          return lastResult
//---------------------------------------------------------------------------------

int getClockSpeed() {

    const uint64_t cycles = getCycles();
    const uint32_t millis = getMillisecondCounter();
    int lastResult = 0;

    for (;;) {

        int n = 1000000;
        while (--n > 0) {}

        const uint32_t milliSecondsElapsed = getMillisecondCounter() - millis;
        const uint64_t cyclesNow = getCycles();

        if (milliSecondsElapsed  > 80) {

            const int newResult = (int) (((cyclesNow - cycles) / milliSecondsElapsed ) / 1000);

            if (milliSecondsElapsed  > 500 || (lastResult == newResult && newResult > 100))
                return newResult;

            lastResult = newResult;
        }
    }
    return lastResult;
}


//---------------------------------------------------------------------------------