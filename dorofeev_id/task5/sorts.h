#pragma once
#include "files.h"

void swap(file* a, file* b);
int name_cmp(const wchar_t* a, const wchar_t* b);
int size_cmp(const long a, const long b, int order);

void bubble_size(file* files, int amount, int order);
void selection_size(file* files, int amount, int order);
void insertion_size(file* files, int amount, int order);
void merge_size(file* files, int left, int middle, int right, int order);
void merge_sort_size(file* files, int left, int right, int order);
int partition_size(file* files, int low, int high, int order);
void hoar_size(file* files, int size, int order);
void shell_size(file* files, int size, int order);
void counting_size(file* files, int size, int order);

void bubble_name(file* files, int amount, int order);
void selection_name(file* files, int amount, int order);
void insertion_name(file* files, int amount, int order);
void merge_name(file* files, int left, int middle, int right, int order);
void merge_sort_name(file* files, int left, int right, int order);
int partition_name(file* files, int low, int high);
void hoar_name(file* files, int size, int order);
void shell_name(file* files, int size, int order);