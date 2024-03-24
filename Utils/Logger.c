#include "Logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

void getFormattedTime() {
    time_t rawTime;
    struct tm *timeInfo;
    time(&rawTime);
    timeInfo = localtime(&rawTime);
    strftime(timeBuffer, 80, "%Y-%m-%d %H:%M:%S", timeInfo);
}

static void printLog(char *level, char *format, va_list args) {
    getFormattedTime();
    FILE *file = fopen(path, "a");
    vsnprintf(msgBuffer, 1024, format, args);
    fprintf(file, "%s [%s]: %s\n", timeBuffer, level, msgBuffer);
    fclose(file);
}

void info(char *format, ...) {
    va_list args;
    va_start(args, format);
    printLog("INFO", format, args);
    va_end(args);
}

void warn(char *format, ...) {
    va_list args;
    va_start(args, format);
    printLog("WARN", format, args);
    va_end(args);
}

Logger createLogger() {
    static int isInit = 0;
    if (isInit) {
        return logger;
    }
    isInit = 1;
    Logger l;
    path = "data/log.txt";
    timeBuffer = (char *)malloc(80);
    msgBuffer = (char *)malloc(1024);
    l.info = info;
    l.warn = warn;
    return l;
}

