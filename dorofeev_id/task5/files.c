#define _CRT_SECURE_NO_WARNINGS
#include "files.h"

file* get_files(char* path, int* file_count)
{
    struct _finddata_t c_file;
    intptr_t hFile;
    int count = 0;
    file* files = NULL; // Initialize to NULL

    // Find first file in directory c:\temp
    if ((hFile = _findfirst(path, &c_file)) == -1L)
        printf("No files in current directory!\n");
    else
    {
        do {
            char date_buffer[30];
            if (count <= 100)
            {
                // Dynamic memory allocation
                files = (file*)realloc(files, (count + 1) * sizeof(file));
                if (files == NULL) {
                    // Handle memory allocation failure
                    printf("Memory allocation failed!\n");
                    exit(EXIT_FAILURE);
                }

                // Copy data to the newly allocated file structure
                snprintf(files[count].name, sizeof(files[count].name), "%s", c_file.name);
                ctime_s(date_buffer, _countof(date_buffer), &c_file.time_write);
                snprintf(files[count].time_created, sizeof(files[count].time_created), "%s", date_buffer);
                files[count].size = c_file.size;

                count++;
            }

        } while (_findnext(hFile, &c_file) == 0 && hFile != -1L);

        _findclose(hFile);
    }

    // Set the file count
    *file_count = count;

    return files;
}


void print_files(file* files, int file_count)
{
    system("cls");
    printf("Listing of files\n\n");
    printf("FILE                                                                           DATE OF CREATION %8c   SIZE(bytes)\n", ' ');
    printf("----                                                                           ---------------- %8c   -----------\n", ' ');
    for (int i = 0; i < file_count; ++i)
    {
        printf("%-78.78s %.24s    %ld\n", files[i].name, files[i].time_created, files[i].size);
    }
    printf("\n\n\n");
}