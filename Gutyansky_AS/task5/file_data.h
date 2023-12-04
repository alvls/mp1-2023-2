#pragma once

#include <time.h>
#include <io.h>

typedef struct {
    char* name;
    time_t time_write;
    _fsize_t size;
} FileData;