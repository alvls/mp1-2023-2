#pragma once
#include "files.h"

int comp_ascending_size(const void* a, const void* b);
int comp_descending_size(const void* a, const void* b);
void swap(file* a, file* b);
void bubble_size(file* files, int amount, int order);
void selection_size(file* files, int amount, int order);
void insertion_size(file* files, int amount, int order);
void merge_size(file* files, int left, int middle, int right, int order);
void merge_sort(file* files, int left, int right, int order);
void shell(file* files, int size, int order);
void counting(file* files, int size, int order);
