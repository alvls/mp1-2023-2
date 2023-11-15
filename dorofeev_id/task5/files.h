#pragma once

typedef struct
{
	char name[256];
	long size; //bytes
} file;


file* get_files(char* path, int* size);

