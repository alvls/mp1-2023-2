#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  
#include <stdlib.h>  
#include <io.h>  
#include <string.h>
#include <time.h>
#include <omp.h>
#include <Windows.h>

#include "file_data.h"
#include "sorting_algorithms.h"

#define STR_(X) #X
#define STR(X) STR_(X)

#define strdup _strdup
#define MAX_PATH_LENGTH 511

size_t get_files_count_in_directory(const char* path);
FileData* get_all_files_from_directory(const char* path, size_t* length);
void read_path(char path[MAX_PATH_LENGTH + 1]);
void sort_menu(char path[MAX_PATH_LENGTH + 1]);
void user_loop(char path[MAX_PATH_LENGTH + 1]);
void benchmark(char path[MAX_PATH_LENGTH + 1]);
void free_files(FileData* files, size_t length);
void reverse(FileData* files, int length);
int try_read_int(int* result, int minValue, int maxValue);

int main(int argc, char* argv[]) {
    int arg_len;
    char path[MAX_PATH_LENGTH + 1];

    if (argc == 2) {
        arg_len = strlen(argv[1]);
        if (argv > MAX_PATH_LENGTH) {
            arg_len = MAX_PATH_LENGTH;
        }
        strncpy(path, argv[1], arg_len);
        path[MAX_PATH_LENGTH] = '\0';

        benchmark(path);

        return 0;
    }

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    read_path(path);
    user_loop(path);

    return 0;
}

void benchmark(char path[MAX_PATH_LENGTH + 1]) {
    int sort_success;
    size_t count;
    FileData* files;
    double begin, end, elapsed_time;

    // Bubble sort
    files = get_all_files_from_directory(path, &count);
    begin = omp_get_wtime();
    sort_success = bubble_sort(files, count);
    end = omp_get_wtime();
    free_files(files, count);
    elapsed_time = end - begin;
    if (!sort_success) elapsed_time = -1;
    printf("Пузырьковая: %lf\n", elapsed_time);
    /// ----------

    // Select sort
    files = get_all_files_from_directory(path, &count);
    begin = omp_get_wtime();
    sort_success = select_sort(files, count);
    end = omp_get_wtime();
    free_files(files, count);
    elapsed_time = end - begin;
    if (!sort_success) elapsed_time = -1;
    printf("Выбором: %lf\n", elapsed_time);
    /// ----------

    // Insert sort
    files = get_all_files_from_directory(path, &count);
    begin = omp_get_wtime();
    sort_success = insert_sort(files, count);
    end = omp_get_wtime();
    free_files(files, count);
    elapsed_time = end - begin;
    if (!sort_success) elapsed_time = -1;
    printf("Вставкой: %lf\n", elapsed_time);
    /// ----------

    // Quick sort
    files = get_all_files_from_directory(path, &count);
    begin = omp_get_wtime();
    sort_success = quick_sort(files, count);
    end = omp_get_wtime();
    free_files(files, count);
    elapsed_time = end - begin;
    if (!sort_success) elapsed_time = -1;
    printf("Хоара: %lf\n", elapsed_time);
    /// ----------

    // Shell sort
    files = get_all_files_from_directory(path, &count);
    begin = omp_get_wtime();
    sort_success = shell_sort(files, count);
    end = omp_get_wtime();
    free_files(files, count);
    elapsed_time = end - begin;
    if (!sort_success) elapsed_time = -1;
    printf("Шелла: %lf\n", elapsed_time);
    /// ----------

    // Merge sort
    files = get_all_files_from_directory(path, &count);
    begin = omp_get_wtime();
    sort_success = merge_sort(files, 0, count, NULL);
    end = omp_get_wtime();
    free_files(files, count);
    elapsed_time = end - begin;
    if (!sort_success) elapsed_time = -1;
    printf("Слиянием: %lf\n", elapsed_time);
    /// ----------

    // Bubble sort
    files = get_all_files_from_directory(path, &count);
    begin = omp_get_wtime();
    sort_success = count_sort(files, count);
    end = omp_get_wtime();
    free_files(files, count);
    elapsed_time = end - begin;
    if (!sort_success) elapsed_time = -1;
    printf("Подсчётом: %lf\n", elapsed_time);
    /// ----------
}

void read_path(char path[MAX_PATH_LENGTH + 1]) {
    int path_read_status;

    do {
        printf("Введите путь до директории и фильтр (С:\\Path\\To\\Folder\\*.* чтобы выбрать все файлы): ");
        path_read_status = scanf("%" STR(MAX_PATH_LENGTH) "[^\n]", path);
        while (getchar() != '\n');
    } while (path_read_status != 1);

    printf("Найдено %llu файлов\n", get_files_count_in_directory(path));
}

void user_loop(char path[MAX_PATH_LENGTH + 1]) {
    int user_choice;

    while (1) {
        do {
            printf("Меню:\n");
            printf("1 - %s\n", path);
            printf("2 - Сортировать\n");
            printf("3 - Выход\n");
            printf(">>> ");
        } while (!try_read_int(&user_choice, 1, 3));

        switch(user_choice) {
        case 1:
            read_path(path);
            break;
        case 2:
            sort_menu(path);
            break;
        case 3:
            return;
        }
    }
}

void sort_menu(char path[MAX_PATH_LENGTH + 1]) {
    int sort_success;
    int sort_method;
    int reverse_sort;
    size_t count;
    FileData* files;
    double begin, end, elapsed_time;
    char time_buffer[30];

    do {
        printf("Выберите метод сортировки:\n");
        printf("1 - пузырьком\n");
        printf("2 - выбором\n");
        printf("3 - вставкой\n");
        printf("4 - Хоара\n");
        printf("5 - Шелла\n");
        printf("6 - Слиянием\n");
        printf("7 - Подсчетом\n");
        printf(">>> ");
    } while (!try_read_int(&sort_method, 1, 7));

    do {
        printf("Сортировать:\n");
        printf("1 - по возрастанию\n");
        printf("2 - по убыванию\n");
        printf(">>> ");
    } while (!try_read_int(&reverse_sort, 1, 2));

    files = get_all_files_from_directory(path, &count);

    begin = omp_get_wtime();
    switch (sort_method) {
    case 1:
        sort_success = bubble_sort(files, count);
        break;
    case 2:
        sort_success = select_sort(files, count);
        break;
    case 3:
        sort_success = insert_sort(files, count);
        break;
    case 4:
        sort_success = quick_sort(files, count);
        break;
    case 5:
        sort_success = shell_sort(files, count);
        break;
    case 6:
        sort_success = merge_sort(files, 0, count, NULL);
        break;
    case 7:
        sort_success = count_sort(files, count);
        break;
    }

    if (reverse_sort == 2) {
        reverse(files, count);
    }

    end = omp_get_wtime();
    elapsed_time = end - begin;

    if (!sort_success) {
        printf("Не удалось отсортировать файлы!\n");
    }
    else {
        printf("Файлы\n\n");
        printf("Файл %20c   Дата %22c   Размер\n", ' ', ' ');
        printf("---- %20c   ---- %22c   ----\n", ' ', ' ');
        for (int i = 0; i < count; i++) {
            ctime_s(time_buffer, _countof(time_buffer), &(files[i].time_write));
            printf("%-25.25s   %-24.24s   %10lu байт\n", files[i].name, time_buffer, files[i].size);
        }

        if (count == 0) {
            printf("Файлы не найдены! Попробуйте выбрать другую директорию.\n");
        }

        printf("Время сортировки: %lfsec\n", elapsed_time);
    }

    free_files(files, count);
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
    if (*length == 0 || (hFile = _findfirst(path, &c_file)) == -1L) {
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
    size_t i;

    for (i = 0; i < length; i++) {
        free(files[i].name);
    }
    free(files);
}

void reverse(FileData* files, int length) {
    int i;

    for (i = 0; i < length / 2; i++) {
        swap(files, i, length - i - 1);
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