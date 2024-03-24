#pragma once
#include <stdio.h>
#include <stdarg.h>

typedef struct {
    void (*info)(char *format, ...);
    void (*warn)(char *format, ...);
} Logger;

extern Logger logger;

static char *path;

static char *timeBuffer;

static char *msgBuffer;

Logger createLogger();