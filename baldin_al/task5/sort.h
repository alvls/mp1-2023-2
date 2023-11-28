#pragma once

#include <memory.h>
#include <time.h>
#include <stdlib.h>  

struct file_info {
    char name[256];
    unsigned long size;
    time_t time_create;
    time_t time_access;
    time_t time_write;
};

void BubbleSort(struct file_info* files, int size);
void SelectSort(struct file_info* files, long size);
void InsertSort(struct file_info* files, long size);
void Merge(struct file_info* files, long lb, long split, long ub);
void MergeSort(struct file_info* files, long lb, long ub);
void HoareSort(struct file_info* files, long N);
int increment(long inc[], long size);
void ShellSort(struct file_info* files, long size);
void CountingSort(struct file_info* files, int size);

