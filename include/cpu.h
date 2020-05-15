#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdbool.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

/* Helper functions to get the CPU frequency */
int getNumberOfProcessors();
static inline uint64_t getCycles();
static inline uint32_t getMillisecondCounter();
int getClockSpeed();

#endif /* CPU_H */