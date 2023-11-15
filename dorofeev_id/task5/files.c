#define _CRT_SECURE_NO_WARNINGS
#include "files.h"
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>


file* get_files(char* path, int* size)
{
	file* files = NULL;
	int count = 0;
	DIR* dir = opendir(path);
	if (dir == NULL)
	{
		printf("Не удалось открыть директорию %s\n", path);
		return NULL;
	}
	struct dirent* entry;
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type == DT_REG)
		{
			count++;
			files = (file*)realloc(files, count * sizeof(file));
			strcpy(files[count - 1].name, entry->d_name);
			char full_path[256];
			sprintf(full_path, "%s/%s", path, entry->d_name);
			struct stat st;
			if (stat(full_path, &st) == 0)
			{
				files[count - 1].size = st.st_size;
			}
			else
			{
				printf("Не удалось получить информацию о файле %s\n", full_path);
				files[count - 1].size = 0;
			}
		}
	}
	closedir(dir);
	*size = count;
	return files;
}
