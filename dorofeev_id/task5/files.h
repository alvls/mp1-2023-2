#pragma once
#include <stdio.h>  
#include <stdlib.h>  
#include <io.h>  
#include <time.h>  
#include <string.h>
#include <wchar.h>

typedef struct
{
	wchar_t name[256];
	wchar_t time_created[30];
	long size; //bytes
} file;


file* get_files(char* path, int* file_count);
void print_files(file* files, int file_count);
