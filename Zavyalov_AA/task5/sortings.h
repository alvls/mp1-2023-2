#pragma once

void sort(struct FileInfo* files, int size, int type, int ascend);
void bubble_sort(struct FileInfo* files, int size, int ascend);
void selection_sort(struct FileInfo* files, int size, int ascend);
void insertion_sort(struct FileInfo* files, int size, int ascend);
void mergeSort(struct FileInfo* files, int ascend, int lb, int ub);
void merge(struct FileInfo* files, int ascend, int lb, int split, int ub);
