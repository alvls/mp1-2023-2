#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <io.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <omp.h>
#include <direct.h>

struct FileInfo {
    char name[260];
    time_t writeTime;
    long fileSize;
};

struct FileInfo currentFile;
struct FileInfo* fileList;
intptr_t fileHandle;

void changeDirectory() {
    printf("Введите путь к директории: ");
    char path[256];
    scanf_s("%s", path, _countof(path));
    if (_chdir(path) != 0) {
        printf("Не удалось изменить директорию. Пожалуйста, проверьте путь и попробуйте снова.\n");
        exit(EXIT_FAILURE);
    }
}

void printAscending(int size) {
    int count = 0;
    printf("\nСписок файлов\n\n");
    printf("Файл         Дата %24c   Размер\n", ' ');
    printf("----         ---- %24c   ----\n", ' ');
    for (int i = 0; i < size; i++) {
        char buffer[30];
        ctime_s(buffer, _countof(buffer), &fileList[i].writeTime);
        if (count <= 20) {
            printf("%-12.12s %.24s  %10ld Байт\n", fileList[i].name, buffer, fileList[i].fileSize);
        }
        count++;
    }
    printf("\nКоличество файлов в директории: %d\n", count);
}

void printDescending(int size) {
    int count = 0;
    printf("\nСписок файлов:\n\n");
    printf("Файл         Дата %24c   Размер\n", ' ');
    printf("----         ---- %24c   ----\n", ' ');
    for (int i = size - 1; i >= 0; i--) {
        char buffer[30];
        ctime_s(buffer, _countof(buffer), &fileList[i].writeTime);
        if (count <= 20) {
            printf("%-12.12s %.24s  %10ld Байт\n", fileList[i].name, buffer, fileList[i].fileSize);
        }
        count++;
    }
    printf("\nКоличество файлов в директории: %d\n", count);
}

void bubbleSort(int size) {
    struct FileInfo temp;
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = size - 1; j > i; j--) {
            if (fileList[j].fileSize < fileList[j - 1].fileSize) {
                temp = fileList[j];
                fileList[j] = fileList[j - 1];
                fileList[j - 1] = temp;
            }
        }
    }
}

void selectionSort(int size) {
    struct FileInfo temp;
    int i, j, k;
    for (i = 0; i < size; i++) {
        k = i;
        temp = fileList[i];
        for (j = i + 1; j < size; j++) {
            if (fileList[j].fileSize < temp.fileSize) {
                k = j;
                temp = fileList[j];
            }
            fileList[k] = fileList[i];
            fileList[i] = temp;
        }
    }
}

void insertionSort(int size) {
    struct FileInfo temp;
    int i, j;
    for (i = 0; i < size; i++) {
        temp = fileList[i];
        for (j = i - 1; j >= 0 && fileList[j].fileSize > temp.fileSize; j--) {
            fileList[j + 1] = fileList[j];
        }
        fileList[j + 1] = temp;
    }
}

void mergeSort1(int left, int mid, int right) {
    struct FileInfo* temp = (struct FileInfo*)malloc((right - left + 1) * sizeof(struct FileInfo));
    int k = 0, i = left, j = mid + 1;
    while (k < (right - left + 1)) {
        while ((i <= mid) && (j <= right)) {
            if (fileList[i].fileSize < fileList[j].fileSize) {
                temp[k] = fileList[i];
                i++;
            }
            else {
                temp[k] = fileList[j];
                j++;
            }
            k++;
        }
        if (i > mid) {
            while (j <= right) {
                temp[k] = fileList[j];
                j++;
                k++;
            }
        }
        else {
            while (i <= mid) {
                temp[k] = fileList[i];
                i++;
                k++;
            }
        }
    }
    for (i = left; i <= right; i++) {
        fileList[i] = temp[i - left];
    }
    free(temp);
}

void mergeSort(int left, int right) {
    int mid;
    if (left == right) {
        return;
    }
    if ((left + right) % 2 != 0) {
        mid = (left + right) / 2;
    }
    else {
        mid = (left + right) / 2;
    }
    mergeSort(left, mid);
    mergeSort(mid + 1, right);
    mergeSort1(left, mid, right);
}

void quickSort(struct FileInfo* array, int size) {
    int i = 0, j = size - 1;
    struct FileInfo temp, p;
    p = array[size >> 1];
    do {
        while (array[i].fileSize < p.fileSize) {
            i++;
        }
        while (array[j].fileSize > p.fileSize) {
            j--;
        }
        if (i <= j) {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    } while (i <= j);
    if (j > 0) {
        quickSort(array, j);
    }
    if (size > i) {
        quickSort(array + i, size - i);
    }
}

void shellSort(int size) {
    int gap = 4, j;
    struct FileInfo temp;
    while (gap > 0) {
        for (int i = 0; i < size; i++) {
            j = i;
            temp = fileList[i];
            while ((j >= gap) && (fileList[j - gap].fileSize > temp.fileSize)) {
                fileList[j] = fileList[j - gap];
                j = j - gap;
            }
            fileList[j] = temp;
        }
        if (gap > 1) {
            gap /= 2;
        }
        else {
            gap = 0;
        }
    }
}

void countingSort(int size) {
    struct FileInfo temp;
    int max, min, i, j;
    min = max = fileList[0].fileSize;
    for (i = 1; i < size; i++) {
        if (fileList[i].fileSize > max) {
            max = fileList[i].fileSize;
        }
        if (fileList[i].fileSize < min) {
            min = fileList[i].fileSize;
        }
    }
    int range = max - min + 1;
    int* count = (int*)malloc(range * sizeof(int));
    struct FileInfo* output = (struct FileInfo*)malloc(size * sizeof(struct FileInfo));
    for (i = 0; i < size; i++) {
        count[i] = 0;
    }
    for (i = 0; i < size; i++) {
        count[fileList[i].fileSize - min]++;
    }
    for (i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }
    for (i = size - 1; i >= 0; i--) {
        output[count[fileList[i].fileSize - min] - 1] = fileList[i];
        count[fileList[i].fileSize - min]--;
    }
    for (i = 0; i < size; i++) {
        fileList[i] = output[i];
    }
    free(count);
    free(output);
}

void copyFiles(struct FileInfo arr[], int size) {
    for (int i = 0; i < size; i++) {
        fileList[i] = arr[i];
    }
}

int ascendingOrDescending() {
    int order;
    printf("\nСортировка по возрастанию или убыванию? (1 - возрастание, 2 - убывание): ");
    scanf_s("%d", &order);
    return order;
}

int exitProgram() {
    int decision;
    printf("\n\nВыйти из программы? (1 - Да, 2 - Нет): ");
    scanf_s("%d", &decision);
    return decision;
}

int main() {
    setlocale(LC_ALL, "Rus");


    changeDirectory();

    if ((fileHandle = _findfirst("*.*", &currentFile)) == -1L) {
        printf("Не найдено ни одного файла.\n");
    }
    else {
        int count = 0;
        do {
            count++;
        } while (_findnext(fileHandle, &currentFile) == 0);
        _findclose(fileHandle);
        fileList = (struct FileInfo*)malloc(count * sizeof(struct FileInfo));
        fileHandle = _findfirst("*.*", &currentFile);
        for (int i = 0; i < count; i++) {
            fileList[i] = currentFile;
            _findnext(fileHandle, &currentFile);
        }
        _findclose(fileHandle);

        printf("\nНачальный список файлов:\n");
        printAscending(count);

        int choice;
        do {
            printf("\nВыберите метод сортировки (1 - пузырек, 2 - выбор, 3 - вставка, 4 - слияние, 5 - Хоара, 6 - Шелла, 7 - подсчет, 0 - выход): ");
            scanf_s("%d", &choice);
            switch (choice) {
            case 1:
                bubbleSort(count);
                break;
            case 2:
                selectionSort(count);
                break;
            case 3:
                insertionSort(count);
                break;
            case 4:
                mergeSort(0, count - 1);
                break;
            case 5:
                quickSort(fileList, count);
                break;
            case 6:
                shellSort(count);
                break;
            case 7:
                countingSort(count);
                break;
            case 0:
                break;
            default:
                printf("\nНеправильный ввод. Повторите попытку.\n");
            }
            if (choice != 0) {
                printf("\nОтсортированный список файлов:\n");
                int order = ascendingOrDescending();
                if (order == 1) {
                    printAscending(count);
                }
                else if (order == 2) {
                    printDescending(count);
                }
            }
        } while (choice != 0);

        free(fileList);
    }

    return 0;
}