#include "../include/cpu.h"
#include "../include/memory.h"
#include <ncurses.h>

int main(int argc, const char* argv[]) {

    int cpuCores = 0;
    int cpuSpeed = 0;
    double cpuSpeedGHz = 0;
    double freeRam, currentRamUsage, totalRam, freeDiskSpace, totalDiskSpace, currentDiskSpace,\
           currentRamUsagePercent, currentDiskUsagePercent;
    char barOut[1024];
    int row, col;
    int ramPercentBar = 0;
    int diskPercentBar = 0;
    int lengthOfBar = 0;

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
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_BLACK, COLOR_BLACK);

    while(1) {
        cpuCores = getNumberOfProcessors();
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
        ramPercentBar = currentRamUsagePercent / 5;
        diskPercentBar = currentDiskUsagePercent / 5;


        attron(COLOR_PAIR(6));
        for(int i = 0; i < 14; i++) {
            for(int j = 0; j < 57; j++) {
                mvprintw(i, j, " ", NULL);
            }
        }
        attron(COLOR_PAIR(1));
        mvprintw(2, 4, "           CMPE 220 Resource Monitor", NULL);
        for(int i = 1; i < 57; i++) {
            mvprintw(0, i, "/", NULL);
            mvprintw(4, i, "/", NULL);
            mvprintw(14, i, "/", NULL);
        }
        for(int i = 0; i < 15; i++)  {
            mvprintw(i, 1, "|", NULL);
            mvprintw(i, 57, "|", NULL);
        }
        attron(COLOR_PAIR(1));
        mvprintw(6, 4, "CPU Cores: ", NULL);
        attron(COLOR_PAIR(2));
        mvprintw(6, 16, "%d", cpuCores);
        attron(COLOR_PAIR(1));
        mvprintw(6, 22, "CPU Speed: ", NULL);
        attron(COLOR_PAIR(2));
        mvprintw(6, 34, "%0.3f GHz", cpuSpeedGHz);
        attron(COLOR_PAIR(1));
        mvprintw(7, 4, "RAM Usage:  [", NULL);
        for(int i = 0; i < ramPercentBar; i++) {
            strcat(barOut, "|");
        }
        if(ramPercentBar < 10) attron(COLOR_PAIR(4));
        else if(ramPercentBar >= 10 && ramPercentBar < 16) attron(COLOR_PAIR(2));
        else if(ramPercentBar >= 16) attron(COLOR_PAIR(3));
        mvprintw(7, 17, "%s", barOut);
        attron(COLOR_PAIR(1));
        mvprintw(7, 37, "]", NULL);
        currentRamUsagePercent > 80.0 ? attron(COLOR_PAIR(3)) : attron(COLOR_PAIR(2));
        mvprintw(7, 39, "%0.2f GB  %0.2f%%", currentRamUsage, currentRamUsagePercent);
        memset(barOut, 0, strlen(barOut));
        attron(COLOR_PAIR(1));
        mvprintw(8, 4, "RAM Available: ", NULL);
        attron(COLOR_PAIR(2));
        mvprintw(8, 20, "%0.2f GB", freeRam);
        attron(COLOR_PAIR(1));
        mvprintw(9, 4, "Total RAM: ", NULL);
        attron(COLOR_PAIR(2));
        mvprintw(9, 16, "%0.2f GB", totalRam);
        attron(COLOR_PAIR(1));
        mvprintw(10, 4, "Disk Usage: [", NULL);
        for(int i = 0; i < diskPercentBar; i++) {
            strcat(barOut, "|");
        }
        if(diskPercentBar < 10) attron(COLOR_PAIR(4));
        else if(diskPercentBar >= 10 && ramPercentBar < 16) attron(COLOR_PAIR(2));
        else if(diskPercentBar >= 16) attron(COLOR_PAIR(3));
        mvprintw(10, 17, "%s", barOut);
        attron(COLOR_PAIR(1));
        mvprintw(10, 37, "]", NULL);
        currentDiskUsagePercent > 80.0 ? attron(COLOR_PAIR(3)) : attron(COLOR_PAIR(2));
        mvprintw(10, 39, "%0.2f GB  %0.2f%%", currentDiskSpace, currentDiskUsagePercent);
        memset(barOut, 0, strlen(barOut));
        attron(COLOR_PAIR(1));
        mvprintw(11, 4, "Available Space: ", NULL);
        attron(COLOR_PAIR(2));
        mvprintw(11, 22, "%0.2f GB", freeDiskSpace);
        attron(COLOR_PAIR(1));
        mvprintw(12, 4, "Total Disk Space: ", NULL);
        attron(COLOR_PAIR(2));
        mvprintw(12, 23, "%0.2f GB", totalDiskSpace);

        refresh();
        sleep(1);
    }

    return 0;
}
