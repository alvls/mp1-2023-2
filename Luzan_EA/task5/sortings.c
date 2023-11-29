#define _CRT_SECURE_NO_WARNINGS
#include "sortings.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>

void swap(struct Files* files, int i, int j) {
    struct Files temp;
    temp = files[i]; files[i] = files[j]; files[j] = temp;
}

int bubbleSort(struct Files* files, int size) {
    int i, j, countSwaps;
    for (i = 0; i < size - 1; i++) {
        countSwaps = 0;
        for (j = 0; j < size - i - 1; j++) {
            if (files[j].size > files[j + 1].size)
            {
                swap(files, j, j + 1); countSwaps++;
            }
        }
        if (countSwaps == 0) { break; }
    }
    return 1;
}

void selectSort(struct Files* a, long size) {
    long i, j, k;
    unsigned long long x;

    for (i = 0; i < size; i++) {   	// i - номер текущего шага
        k = i;
        x = a[i].size;

        for (j = i + 1; j < size; j++)	// цикл выбора наименьшего элемента
            if (a[j].size < x) {
                k = j; x = a[j].size;	        // k - индекс наименьшего элемента
            }
        swap(a, i, k);
        a[i].size = x;   	// меняем местами наименьший с a[i]
    }
}

void insertSort(struct Files* a, long size) {
    unsigned long long x;
    long i, j;

    for (i = 0; i < size; i++) {  // цикл проходов, i - номер прохода
        x = a[i].size;

        // поиск места элемента в готовой последовательности 
        for (j = i - 1; j >= 0 && a[j].size > x; j--)
            swap(a, j + 1, j); // сдвигаем элемент направо, пока не дошли

        // место найдено, вставить элемент
        a[j + 1].size = x;
    }
}

void merge(struct Files* a, long lb, long split, long ub) {
    // Слияние упорядоченных частей массива в буфер temp
    // с дальнейшим переносом содержимого temp в a[lb]...a[ub]

      // текущая позиция чтения из первой последовательности a[lb]...a[split]
    long pos1 = lb;

    // текущая позиция чтения из второй последовательности a[split+1]...a[ub]
    long pos2 = split + 1;

    // текущая позиция записи в temp
    long pos3 = 0;

    struct Files* temp = (struct Files*)malloc(sizeof(struct Files) * (ub - lb + 1));

    // идет слияние, пока есть хоть один элемент в каждой последовательности
    while (pos1 <= split && pos2 <= ub) {
        if (a[pos1].size < a[pos2].size) {
            temp[pos3++].size = a[pos1++].size;
            strcpy(temp[pos3++].name, a[pos1++].name);
        }
        else
            temp[pos3++] = a[pos2++];
    }

    // одна последовательность закончилась - 
    // копировать остаток другой в конец буфера 
    while (pos2 <= ub)   // пока вторая последовательность непуста 
        temp[pos3++] = a[pos2++];
    while (pos1 <= split)  // пока первая последовательность непуста
        temp[pos3++] = a[pos1++];

    // скопировать буфер temp в a[lb]...a[ub]
    for (pos3 = 0; pos3 < ub - lb + 1; pos3++) {
        a[lb + pos3].size = temp[pos3].size;
        strcpy(a[lb + pos3].name, temp[pos3].name);
    }
    free(temp);
}

void mergeSort(struct Files* a, long lb, long ub) {
    long split;                   // индекс, по которому делим массив

    if (lb < ub) {                // если есть более 1 элемента

        split = (lb + ub) / 2;

        mergeSort(a, lb, split);       // сортировать левую половину 
        mergeSort(a, split + 1, lb);// сортировать правую половину 
        merge(a, lb, split, ub);    // слить результаты в общий массив
    }
}

int quickSort(struct Files* files, int size) {
    int i, j;
    unsigned long long int center_size;

    if (size == 0) return 1;

    i = 0;
    j = size - 1;
    center_size = files[size / 2].size;

    do {
        while (files[i].size < center_size) i++;
        while (files[j].size > center_size) j--;

        if (i <= j) {
            swap(files, i, j);
            i++;
            j--;
        }
    } while (i <= j);

    if (j > 0) quickSort(files, i);
    if (size > i) quickSort(files + i, size - i);

    return 1;
}

int increment(long inc[], long size) {
    int p1, p2, p3, s;

    p1 = p2 = p3 = 1;
    s = -1;
    do {
        if (++s % 2) {
            inc[s] = 8 * p1 - 6 * p2 + 1;
        }
        else {
            inc[s] = 9 * p1 - 9 * p3 + 1;
            p2 *= 2;
            p3 *= 2;
        }
        p1 *= 2;
    } while (3 * inc[s] < size);

    return s > 0 ? --s : 0;
}

void shellSort(struct Files* a, long size) {
    long inc, i, j, seq[40];
    int s;

    // вычисление последовательности приращений
    s = increment(seq, size);
    while (s >= 0) {
        // сортировка вставками с инкрементами inc[] 
        inc = seq[s--];

        for (i = inc; i < size; i++) {
            struct Files* temp = (struct Files*)malloc(sizeof(struct Files));
            temp[0].size = a[i].size;
            strcpy(temp[0].name, a[i].name);
            for (j = i - inc; (j >= 0) && (a[j].size > temp[0].size); j -= inc) {
                //a[j + inc].size = a[j].size;
                //strcpy(a[j + inc].name, a[j].name);
                swap(a, j + inc, j);
            }
            a[j + inc].size = temp[0].size;
            strcpy(a[j + inc].name, temp[0].name);
        }
    }
}

int countingSort(struct Files* array, int n) {
    if (n <= 1) {
        return 0;  // Массив уже отсортирован или содержит 0 или 1 элемент.
    }

    // Находим минимальное и максимальное значения размеров файлов.
    unsigned long long int minSize = ULLONG_MAX, maxSize = 0;
    for (int i = 0; i < n; ++i) {
        if (array[i].size < minSize) {
            minSize = array[i].size;
        }
        if (array[i].size > maxSize) {
            maxSize = array[i].size;
        }
    }

    // Вычисляем диапазон размеров для создания массива подсчета.
    unsigned long long int range = maxSize - minSize + 1;

    // Создаем массив подсчета и инициализируем его нулями.
    unsigned long long int* count = (unsigned long long int*)malloc(range * sizeof(unsigned long long int));
    memset(count, 0, range * sizeof(unsigned long long int));

    // Считаем количество каждого размера файла.
    for (int i = 0; i < n; ++i) {
        count[array[i].size - minSize]++;
    }

    // Восстанавливаем отсортированный массив.
    int idx = 0;
    for (unsigned long long int size = minSize; size <= maxSize; ++size) {
        while (count[size - minSize] > 0) {
            array[idx].size = size;
            idx++;
            count[size - minSize]--;
        }
    }

    // Освобождаем память, выделенную для массива подсчета.
    free(count);
    return 0;
}
