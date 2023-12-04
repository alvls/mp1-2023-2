#pragma once

void sort(struct FileInfo* files, int size, int type, int ascend);
void bubbleSort(struct FileInfo* files, int size, int ascend);
void selectionSort(struct FileInfo* files, int size, int ascend);
void insertionSort(struct FileInfo* files, int size, int ascend);
void mergeSort(struct FileInfo* files, int ascend, int lb, int ub);
int partition(struct FileInfo* files, int low, int high, int ascend);
void merge(struct FileInfo* files, int ascend, int lb, int split, int ub);
void quickSort(struct FileInfo* files, int lo, int hi, int ascend);
void shellSort(struct FileInfo* files, int n, int ascend);
void countingSort(struct FileInfo* files, int size, int ascend);