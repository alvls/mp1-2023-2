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
void bubble_sort(FileData* files, int length);
void select_sort(FileData* files, int length);
void insert_sort(FileData* files, int length);
void quick_sort(FileData* files, int length);
void shell_sort(FileData* files, int length);
int try_read_int(int* result, int minValue, int maxValue);

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

    int sort_method = 0;
    do {
        printf("Выберите метод сортировки:\n");
        printf("1 - пузырьком\n");
        printf("2 - выбором\n");
        printf("3 - вставкой\n");
        printf("4 - Хоара (быстрая сортировка)\n");
        printf("5 - Шелла\n");
    } while (!try_read_int(&sort_method, 1, 5));

    begin = clock();
    switch (sort_method) {
    case 1:
        bubble_sort(files, count);
        break;
    case 2:
        select_sort(files, count);
        break;
    case 3:
        insert_sort(files, count);
        break;
    case 4:
        quick_sort(files, count);
        break;
    case 5:
        shell_sort(files, count);
        break;
    }
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

void bubble_sort(FileData* files, int length) {
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

void select_sort(FileData* files, int length) {
    int i, j, min_index;
    _fsize_t min_size;

    for (i = 0; i < length; i++) {
        min_index = i;
        min_size = files[i].size;

        for (j = i + 1; j < length; j++) {
            if (files[j].size < min_size) {
                min_index = j;
                min_size = files[j].size;
            }
        }

        swap(files, i, min_index);
    }
}

void insert_sort(FileData* files, int length) {
    int i, j;
    FileData current_element;

    for (i = 1; i < length; i++) {
        current_element = files[i];
        
        j = i - 1;
        while (j >= 0 && files[j].size > current_element.size) {
            files[j + 1] = files[j];
            --j;
        }

        files[j + 1] = current_element;
    }
}

void quick_sort(FileData* files, int length) {
    int i, j;
    _fsize_t center_size;

    i = 0;
    j = length - 1;
    center_size = files[length / 2].size;

    do {
        while (files[i].size < center_size) i++;
        while (files[j].size > center_size) j--;

        if (i <= j) {
            swap(files, i, j);
            i++;
            j--;
        }
    } while (i <= j);

    if (j > 0) quick_sort(files, i);
    if (length > i) quick_sort(files + i, length - i);
}

void shell_sort(FileData* files, int length) {
    int s, i, j;
    FileData current_element;

    for (s = length / 2; s > 0; s /= 2) {
        for (i = s; i < length; ++i) {
            current_element = files[i];

            j = i - 1;
            while (j >= 0 && files[j].size > current_element.size) {
                files[j + 1] = files[j];
                --j;
            }

            files[j + 1] = current_element;
        }
    }
}

int try_read_int(int* result, int minValue, int maxValue) {
    int read_arguments;

    read_arguments = scanf_s("%d", result);
    while (getchar() != '\n');
    if (read_arguments == 1 && *result >= minValue && *result <= maxValue) {
        return 1;
    }

    return 0;
}