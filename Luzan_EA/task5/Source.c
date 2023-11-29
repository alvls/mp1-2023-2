#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include "sortings.h"
#include <string.h>
#include <windows.h>
#include <omp.h> //for time
#include <memory.h> //
#include <locale.h>
#include <limits.h>


int makeArray(struct Files* list, char* path) { 

    WIN32_FIND_DATAA file_info;
    HANDLE file; 

    file = FindFirstFileA(path, &file_info); 

    int i = 0;
    do {
        if (strcmp(file_info.cFileName, ".") != 0 && strcmp(file_info.cFileName, "..") != 0) {
            strcpy(list[i].name, file_info.cFileName);
            list[i].size = file_info.nFileSizeHigh * (MAXDWORD + 1) + file_info.nFileSizeLow;
            i++;
        }
    } while (FindNextFileA(file, &file_info) != 0); 


    return 0;
}

char* getPath() {
    printf("Enter directory path: ");
    char* path = (char*)malloc(MAX_PATH * sizeof(char));
    //from windows.h == 260
    scanf("%s", path);
    strcat(path, "\\*"); //from string.h
    return path;
}

int countFiles(char* path) {
    WIN32_FIND_DATAA file_info;
    HANDLE file;

    file = FindFirstFileA(path, &file_info);
    if (file == INVALID_HANDLE_VALUE) {
        return -1;
    }
    int count = 0;
    do {
        if (strcmp(file_info.cFileName, ".") != 0 && strcmp(file_info.cFileName, "..") != 0) {
            count++;
        }
    } while (FindNextFileA(file, &file_info) != 0);

    FindClose(file);
    return count;
}

void printFiles(struct Files* arr, int len) {
    printf("FILE  %24c  SIZE\n", ' ');
    printf("----  %24c  ----\n", ' ');
    for (int i = 0; i < len; i++) {
        printf("%-20.20s      %10llu\n", arr[i].name, arr[i].size);
    }
    printf("--------------------------------------------------------------\n");
}

void printFilesRev(struct Files* arr, int len) {
    printf("FILE  %24c  SIZE\n", ' ');
    printf("----  %24c  ----\n", ' ');
    for (int i = len - 1; i >= 0; i--) {
        printf("%-20.20s      %10llu\n", arr[i].name, arr[i].size);
    }
    printf("--------------------------------------------------------------\n");
}

int Sort(struct Files* arr, int len) { 
    int sortType = 100;

    printf("Enter the sorting method: \n");
    printf("1 - BubbleSort, 2 - SelectSort, 3 - insertSort\n");
    printf("4 - mergeSort, 5 - quickSort, 6 - shellSort\n");
    printf("7 - CountingSort !(be careful, if have very big files)\n");
    printf("Your choice: ");
    scanf("%i", &sortType);
    scanf("%*[^\n]"); // убираем лишние символы до \n, не включительно
                      // delete all symbols till \n, not including \n
    getchar(); // delete \n

    while ((sortType > 7) || (sortType < 1)) {
        printf("There is no sort method with such name. Please, try again");
        scanf("%i", &sortType);
        scanf("%*[^\n]");
        getchar();
    }

    double start = 0;
    double end = 0;
    int sl = 0;
    switch (sortType) {
    case 1:
        start = omp_get_wtime();
        bubbleSort(arr, len);
        end = omp_get_wtime();
        break;
    case 2:
        start = omp_get_wtime();
        selectSort(arr, len);
        end = omp_get_wtime();
        break;
    case 3:
        start = omp_get_wtime();
        insertSort(arr, len);
        end = omp_get_wtime();
        break;
    case 4:
        start = omp_get_wtime();
        mergeSort(arr, 0, len - 1);
        end = omp_get_wtime();
        break;
    case 5:
        start = omp_get_wtime();
        quickSort(arr, len);
        end = omp_get_wtime();
        break;
    case 6:
        start = omp_get_wtime();
        shellSort(arr, len);
        end = omp_get_wtime();
        break;
    case 7:
        start = omp_get_wtime();
        sl = countingSort(arr, len);
        end = omp_get_wtime();
        break;
    default:   return -1; // никогда не будет выполнен, т.к. проверка реализована выше
                          // will never be executed, because there is a check higher
    }
    if (sl == -1) { return 0; }
    char revSortTrue = 'i';
    printf("Do you want the reverse sort? (the biggest file is the highest in the list) \n[y/n]: ");
    do { 
        scanf("%c", &revSortTrue);
        scanf("%*[^\n]"); 
        getchar(); 

        if (revSortTrue == 'n') { printFiles(arr, len); }
        else {
            if (revSortTrue == 'y') { printFilesRev(arr, len); }
            else { printf("Incorrect input. Enter 'y' or 'n': "); revSortTrue = 'i'; }
        }
    } while (revSortTrue == 'i');

    printf_s("Work took %f sec. time.\n\n\n", end - start);

    return 0;
}

struct Files* cpyArr(struct Files* arr, int len) { // saving Arr
    struct Files* arrCpy = (struct Files*)malloc(sizeof(struct Files) * len);
    for (int i = 0; i < len; i++) {
        arrCpy[i].size = arr[i].size;
        strcpy(arrCpy[i].name, arr[i].name);
    }
    return arrCpy;
}


void main() {
    setlocale(LC_ALL, "ru");
    char* path = (char*)malloc(MAX_PATH * sizeof(char));
    char inp = 'd';
    int count = 0;
    struct Files* list = (struct Files*)malloc(sizeof(struct Files) * 1);
    //при первом запуске будет исполнено if
    // if will be executed first time, free(list) on 195

    while (1) {
        if (inp == 'd') {
            count = 0;
            while ((count == 0) || (count == -1)) {
                free(path);
                strcpy(path, getPath());
                count = countFiles(path);

                if (count == -1) {
                    printf("Couldn read your directory, please choose another one\n");
                    continue;
                }
                if (count == 0) {
                    printf("Your directory is empty, please choose another one\n");
                    continue;
                }
            }
            free(list);
            list = (struct Files*)malloc(sizeof(struct Files) * count);
            makeArray(list, path);
        }

        int sortSuccess = Sort(cpyArr(list, count), count);
        while (sortSuccess == -1) {
            printf("There is no sort method with such name. Please try again\n");
            sortSuccess = Sort(cpyArr(list, count), count);
        }

        printf("Do you want to change sort method (s), change directory(d) or exit(e)? \n");
        inp = ' ';
        do {
            scanf("%c", &inp);
            scanf("%*[^\n]");
            getchar();
        } while ((inp != 's') && (inp != 'd') && (inp != 'e'));

        if (inp == 'e') { printf("Goodbye"); break; }
    }
}
