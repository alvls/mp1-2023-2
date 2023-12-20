#pragma once

#include <io.h>  
#include <time.h>

typedef struct
{
    char* name;
    time_t time_write;
    _fsize_t size;
} file_info;