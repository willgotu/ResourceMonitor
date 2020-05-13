#include "cpu.c"
#include "../include/memory.h"
#include <ncurses.h>

int main(int argc, const char* argv[]) {
    int cpu = 0;
    int cpuSpeed = 0;
    double cpuSpeedGHz = 0;
    double freeRam, currentRamUsage, totalRam, freeDiskSpace, totalDiskSpace, currentDiskSpace;
    double currentRamUsagePercent, currentDiskUsagePercent;

    cpu = getCpuInfo();
    // memory = callMemoryUsage(); // RAM Usage
    // disk = getLogicalDiskInfo();
    // diskSpace = getDiskSpace(argv[1]);

    initscr();
    curs_set(0);

    /* initialize colors */
    if(has_colors() == FALSE) {
        endwin();
        printf("Terminal does not support colors\n");
        exit(1);
    }

    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);

    while(1){
        cpuSpeed = getClockSpeed();
        cpuSpeedGHz = (double) cpuSpeed / 1000.0;
        freeRam = getAvailableMemory();
        totalRam = getTotalMemory();
        currentRamUsage = getCurrentMemoryUsage();
        freeDiskSpace = getAvailableDiskSpace();
        totalDiskSpace = getTotalDiskSpace();
        currentDiskSpace = getCurrentDiskSpace();
        currentRamUsagePercent = (currentRamUsage / totalRam) * 100.0;
        currentDiskUsagePercent = (currentDiskSpace / totalDiskSpace) * 100.0;

        attron(COLOR_PAIR(1));
        mvprintw(1, 0, "CPU Speed: ", NULL);
        cpuSpeedGHz > 3.50 ? attron(COLOR_PAIR(3)) : attron(COLOR_PAIR(2));
        mvprintw(1, 12, "%0.3f GHz", cpuSpeedGHz);
        attron(COLOR_PAIR(1));
        mvprintw(2, 0, "RAM Usage: ", NULL);
        currentRamUsagePercent > 70.0 ? attron(COLOR_PAIR(3)) : attron(COLOR_PAIR(2));
        mvprintw(2, 12, "%0.2f GB  %0.2f%%", currentRamUsage, currentRamUsagePercent);
        attron(COLOR_PAIR(1));
        mvprintw(3, 0, "RAM Available: ", NULL);
        attron(COLOR_PAIR(2));
        mvprintw(3, 16, "%0.2f GB", freeRam);
        attron(COLOR_PAIR(1));
        mvprintw(4, 0, "Total RAM: ", NULL);
        attron(COLOR_PAIR(2));
        mvprintw(4, 12, "%0.2f GB", totalRam);
        attron(COLOR_PAIR(1));
        mvprintw(5, 0, "Disk Usage: ", NULL);
        currentDiskUsagePercent > 70.0 ? attron(COLOR_PAIR(3)) : attron(COLOR_PAIR(2));
        mvprintw(5, 13, "%0.2f GB  %0.2f%%", currentDiskSpace, currentDiskUsagePercent);
        attron(COLOR_PAIR(1));
        mvprintw(6, 0, "Available Space: ", NULL);
        attron(COLOR_PAIR(2));
        mvprintw(6, 18, "%0.2f GB", freeDiskSpace);
        attron(COLOR_PAIR(1));
        mvprintw(7, 0, "Total Disk Space: ", NULL);
        attron(COLOR_PAIR(2));
        mvprintw(7, 19, "%0.2f GB", totalDiskSpace);
        refresh();
        sleep(1);
    }

    return 0;
}