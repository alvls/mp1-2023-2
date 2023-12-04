#define _CRT_SECURE_NO_WARNINGS
#include "files.h"
#include <wchar.h>
#include <time.h>

file* get_files(wchar_t* path, int* file_count)
{
    struct _wfinddata_t c_file;
    intptr_t hFile;
    int count = 0;
    file* files = NULL; // Initialize to NULL

    // Find first file in directory c:\temp
    if ((hFile = _wfindfirst(path, &c_file)) == -1L)
        wprintf(L"No files in current directory!\n");
    else
    {
        do {
            wchar_t date_buffer[30];
            if (count <= 999999)
            {
                // Dynamic memory allocation
                files = (file*)realloc(files, (count + 1) * sizeof(file));
                if (files == NULL) {
                    // Handle memory allocation failure
                    wprintf(L"Memory allocation failed!\n");
                    exit(EXIT_FAILURE);
                }

                // Copy data to the newly allocated file structure
                wcsncpy(files[count].name, c_file.name, sizeof(files[count].name) / sizeof(files[count].name[0]) - 1);
                files[count].name[sizeof(files[count].name) / sizeof(files[count].name[0]) - 1] = L'\0'; // Ensure null-terminated

                time_t raw_time = c_file.time_write;
                struct tm time_info;
                localtime_s(&time_info, &raw_time);

                wcsftime(date_buffer, sizeof(date_buffer) / sizeof(date_buffer[0]), L"%Y-%m-%d %H:%M:%S", &time_info);
                wcsncpy(files[count].time_created, date_buffer, sizeof(files[count].time_created) / sizeof(files[count].time_created[0]) - 1);
                files[count].time_created[sizeof(files[count].time_created) / sizeof(files[count].time_created[0]) - 1] = L'\0'; // Ensure null-terminated

                files[count].size = c_file.size;

                count++;
            }

        } while (_wfindnext(hFile, &c_file) == 0 && hFile != -1L);

        _findclose(hFile);
    }

    // Set the file count
    *file_count = count;

    return files;
}

void print_files(file* files, int file_count)
{
    system("cls");
    wprintf(L"Listing of files\n\n");
    wprintf(L"FILE                                                                           DATE OF CREATION %8c   SIZE(bytes)\n", ' ');
    wprintf(L"----                                                                           ---------------- %8c   -----------\n", ' ');
    for (int i = 0; i < file_count; ++i)
    {
        wprintf(L"%-78.78ls %.19ls    %ld\n", files[i].name, files[i].time_created, files[i].size);
    }
    wprintf(L"\n\n\n");
}
