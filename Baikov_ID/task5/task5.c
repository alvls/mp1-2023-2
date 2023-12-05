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

struct _finddata_t currentFileWindows;
struct _finddata_t* fileListWindows;
intptr_t fileHandleWindows;

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
        ctime_s(buffer, _countof(buffer), &fileListWindows[i].time_write);
        if (count <= 20) {
            printf("%-12.12s %.24s  %10ld Байт\n", fileListWindows[i].name, buffer, fileListWindows[i].size);
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
        ctime_s(buffer, _countof(buffer), &fileListWindows[i].time_write);
        if (count <= 20) {
            printf("%-12.12s %.24s  %10ld Байт\n", fileListWindows[i].name, buffer, fileListWindows[i].size);
        }
        count++;
    }
    printf("\nКоличество файлов в директории: %d\n", count);
}

void bubbleSort(int size) {
    struct _finddata_t tempFile;
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = size - 1; j > i; j--) {
            if (fileListWindows[j].size < fileListWindows[j - 1].size) {
                tempFile = fileListWindows[j];
                fileListWindows[j] = fileListWindows[j - 1];
                fileListWindows[j - 1] = tempFile;
            }
        }
    }
}

void selectionSort(int size) {
    struct _finddata_t tempFile;
    int i, j, k;
    for (i = 0; i < size; i++) {
        k = i;
        tempFile = fileListWindows[i];
        for (j = i + 1; j < size; j++) {
            if (fileListWindows[j].size < tempFile.size) {
                k = j;
                tempFile = fileListWindows[j];
            }
            fileListWindows[k] = fileListWindows[i];
            fileListWindows[i] = tempFile;
        }
    }
}

void insertionSort(int size) {
    struct _finddata_t tempFile;
    int i, j;
    for (i = 0; i < size; i++) {
        tempFile = fileListWindows[i];
        for (j = i - 1; j >= 0 && fileListWindows[j].size > tempFile.size; j--) {
            fileListWindows[j + 1] = fileListWindows[j];
        }
        fileListWindows[j + 1] = tempFile;
    }
}

void mergeSort1(int left, int mid, int right) {
    struct _finddata_t* tempFile = (struct _finddata_t*)malloc((right - left + 1) * sizeof(struct _finddata_t));
    int k = 0, i = left, j = mid + 1;
    while (k < (right - left + 1)) {
        while ((i <= mid) && (j <= right)) {
            if (fileListWindows[i].size < fileListWindows[j].size) {
                tempFile[k] = fileListWindows[i];
                i++;
            }
            else {
                tempFile[k] = fileListWindows[j];
                j++;
            }
            k++;
        }
        if (i > mid) {
            while (j <= right) {
                tempFile[k] = fileListWindows[j];
                j++;
                k++;
            }
        }
        else {
            while (i <= mid) {
                tempFile[k] = fileListWindows[i];
                i++;
                k++;
            }
        }
    }
    for (i = left; i <= right; i++) {
        fileListWindows[i] = tempFile[i - left];
    }
    free(tempFile);
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

void quickSort(struct _finddata_t* array, int size) {
    int i = 0, j = size - 1;
    struct _finddata_t tempFile, pivot;
    pivot = array[size >> 1];
    do {
        while (array[i].size < pivot.size) {
            i++;
        }
        while (array[j].size > pivot.size) {
            j--;
        }
        if (i <= j) {
            tempFile = array[i];
            array[i] = array[j];
            array[j] = tempFile;
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
    struct _finddata_t tempFile;
    while (gap > 0) {
        for (int i = 0; i < size; i++) {
            j = i;
            tempFile = fileListWindows[i];
            while ((j >= gap) && (fileListWindows[j - gap].size > tempFile.size)) {
                fileListWindows[j] = fileListWindows[j - gap];
                j = j - gap;
            }
            fileListWindows[j] = tempFile;
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
    long maxFileSize = fileListWindows[0].size;
    for (int i = 1; i < size; i++) {
        if (fileListWindows[i].size > maxFileSize) {
            maxFileSize = fileListWindows[i].size;
        }
    }
    long* count = (long*)malloc((maxFileSize + 1) * sizeof(long));
    for (long i = 0; i <= maxFileSize; i++) {
        count[i] = 0;
    }
    for (int i = 0; i < size; i++) {
        count[fileListWindows[i].size]++;
    }
    for (long i = 1; i <= maxFileSize; i++) {
        count[i] += count[i - 1];
    }

    struct _finddata_t* tempFile = (struct _finddata_t*)malloc(size * sizeof(struct _finddata_t));

    for (int i = size - 1; i >= 0; i--) {
        tempFile[count[fileListWindows[i].size] - 1] = fileListWindows[i];
        count[fileListWindows[i].size]--;
    }

    for (int i = 0; i < size; i++) {
        fileListWindows[i] = tempFile[i];
    }

    free(count);
    free(tempFile);
}

void copyFiles(struct _finddata_t arr[], int size) {
    for (int i = 0; i < size; i++) {
        fileListWindows[i] = arr[i];
    }
}

int ascendingOrDescending() {
    int choice;
    printf("\nСортировка по возрастанию или убыванию? (1 - возрастание, 2 - убывание): ");
    scanf_s("%d", &choice);
    return choice;
}

int exitProgram() {
    int choice;
    printf("\n\nВыйти из программы? (1 - Да, 2 - Нет): ");
    scanf_s("%d", &choice);
    return choice;
}

int main() {
    setlocale(LC_ALL, "Rus");

    changeDirectory();

    if ((fileHandleWindows = _findfirst("*.*", &currentFileWindows)) == -1L) {
        printf("Не найдено ни одного файла.\n");
    }
    else {
        int count = 0;
        do {
            count++;
        } while (_findnext(fileHandleWindows, &currentFileWindows) == 0);
        _findclose(fileHandleWindows);
        fileListWindows = (struct _finddata_t*)malloc(count * sizeof(struct _finddata_t));
        fileHandleWindows = _findfirst("*.*", &currentFileWindows);
        for (int i = 0; i < count; i++) {
            fileListWindows[i] = currentFileWindows;
            _findnext(fileHandleWindows, &currentFileWindows);
        }
        _findclose(fileHandleWindows);

        printf("\nНачальный список файлов:\n");
        printAscending(count);

        int choice;
        do {
            printf("\nВыберите метод сортировки (1 - пузырек, 2 - выбор, 3 - вставка, "
                "4 - слияние, 5 - Хоара, 6 - Шелла, 7 - подсчет, 0 - выход: ");
            scanf_s("%d", &choice);

            double startTime, endTime;

            switch (choice) {
            case 1:
                startTime = omp_get_wtime();
                bubbleSort(count);
                endTime = omp_get_wtime();
                break;
            case 2:
                startTime = omp_get_wtime();
                selectionSort(count);
                endTime = omp_get_wtime();
                break;
            case 3:
                startTime = omp_get_wtime();
                insertionSort(count);
                endTime = omp_get_wtime();
                break;
            case 4:
                startTime = omp_get_wtime();
                mergeSort(0, count - 1);
                endTime = omp_get_wtime();
                break;
            case 5:
                startTime = omp_get_wtime();
                quickSort(fileListWindows, count);
                endTime = omp_get_wtime();
                break;
            case 6:
                startTime = omp_get_wtime();
                shellSort(count);
                endTime = omp_get_wtime();
                break;
            case 7:
                startTime = omp_get_wtime();
                countingSort(count);
                endTime = omp_get_wtime();
                break;
                //           case 8: 
                //               changeDirectory();
                //               break;
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
            printf("\nВремя выполнения: %f секунд\n", endTime - startTime);
        } while (choice != 0);

        free(fileListWindows);
    }

    return 0;
}