#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  
#include <stdlib.h>  
#include <io.h>  
#include <string.h>
#include <time.h>
#include <Windows.h>

#define strdup _strdup

typedef struct {
    char* name;
    time_t time_write;
    _fsize_t size;
} FileData;

size_t get_files_count_in_directory(const char* path);
FileData* get_all_files_from_directory(const char* path, size_t* length);
void free_files(FileData* files, size_t length);
void swap(FileData* files, int i, int j);
void bubble_sort(FileData* files, size_t length);

int main(void)
{
    const char* path = "D:\\Downloads\\*.*";
    size_t count;
    FileData* files;
    time_t begin, end;
    double elapsed_time;
    char time_buffer[30];

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    files = get_all_files_from_directory(path, &count);

    begin = clock();
    bubble_sort(files, count);
    end = clock();
    elapsed_time = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Listing of files\n\n");
    printf("FILE         DATE %24c   SIZE\n", ' ');
    printf("----         ---- %24c   ----\n", ' ');
    for (int i = 0; i < count; i++) {
        ctime_s(time_buffer, _countof(time_buffer), &(files[i].time_write));
        printf("%-12.12s %.24s  %10lu\n", files[i].name, time_buffer, files[i].size);
    }

    printf("Elapsed time: %lfsec\n", elapsed_time);

    free_files(files, count);

    system("pause");
}

size_t get_files_count_in_directory(const char* path) {
    struct _finddata_t c_file;
    intptr_t hFile;
    size_t count = 0;

    if ((hFile = _findfirst(path, &c_file)) == -1L)
        return 0;
    else
    {
        do {
            if (!(c_file.attrib & _A_SUBDIR)) {
                count++;
            }
        } while (_findnext(hFile, &c_file) == 0);
        _findclose(hFile);
    }

    return count;
}

FileData* get_all_files_from_directory(const char* path, size_t* length) {
    struct _finddata_t c_file;
    intptr_t hFile;
    FileData* files;
    int index;

    *length = get_files_count_in_directory(path);

    index = 0;
    if (*length == 0 || (hFile = _findfirst("D:\\Downloads\\*.*", &c_file)) == -1L) {
        return NULL;
    }
    
    files = (FileData*)malloc(sizeof(FileData) * *length);
    do {
        if (!(c_file.attrib & _A_SUBDIR)) {
            if (index >= *length) {
                break;
            }

            FileData data;
            data.name = strdup(c_file.name);
            data.time_write = c_file.time_write;
            data.size = c_file.size;

            files[index++] = data;
        }
    } while (_findnext(hFile, &c_file) == 0);
    _findclose(hFile);

    return files;
}

void free_files(FileData* files, size_t length) {
    for (size_t i = 0; i < length; i++) {
        free(files[i].name);
    }
    free(files);
}

void swap(FileData* files, int i, int j) {
    FileData temp = files[i];
    files[i] = files[j];
    files[j] = temp;
}

void bubble_sort(FileData* files, size_t length)
{
    int i, j, swaps;
    for (i = 0; i < length - 1; i++) {
        swaps = 0;
        for (j = 0; j < length - i - 1; j++) {
            if (files[j].size > files[j + 1].size) {
                swap(files, j, j + 1);
                swaps++;
            }
        }

        if (swaps == 0) {
            break;
        }
    }
}