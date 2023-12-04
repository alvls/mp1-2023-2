#pragma once

#include "file_data.h"

void swap(FileData* files, int i, int j);
int bubble_sort(FileData* files, int length);
int select_sort(FileData* files, int length);
int insert_sort(FileData* files, int length);
int quick_sort(FileData* files, int length);
int shell_sort(FileData* files, int length);
int merge_sort(FileData* files, int lower_bound, int upper_bound, FileData* buffer);
int count_sort(FileData* files, int length);