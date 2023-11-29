#pragma once
#pragma once
#include <windows.h>

typedef struct Files {
    char name[MAX_PATH];
    unsigned long long int size;
};

void swap(struct Files* files, int i, int j);

int bubbleSort(struct Files* files, int size);

void selectSort(struct Files* a, long size);

void insertSort(struct Files* a, long size);

void merge(struct Files* a, long lb, long split, long ub);

void mergeSort(struct Files* a, long lb, long ub); //nt

int quickSort(struct Files* files, int size); //_

void shellSort(struct Files* a, long size);

int countingSort(struct Files* array, int n);