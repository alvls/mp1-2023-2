#pragma once
#include "files.h"

int comp_ascending_size(const void* a, const void* b);
int comp_descending_size(const void* a, const void* b);
void swap(file* a, file* b);
void bubble_size(file* files, int amount, int order);
void selection_size(file* files, int amount, int order);
void insertion_size(file* files, int amount, int order);
void merge_size(file* files, int left, int middle, int right, int order);
void merge_sort_size(file* files, int left, int right, int order);
void hoar_size(file* files, int size, int order);
void shell_size(file* files, int size, int order);
void counting_size(file* files, int size, int order);

int comp_ascending_name(const void* a, const void* b);
int comp_descending_name(const void* a, const void* b);
void bubble_name(file* files, int amount, int order);
void selection_name(file* files, int amount, int order);
void insertion_name(file* files, int amount, int order);
void merge_name(file* files, int left, int middle, int right, int order);
void merge_sort_name(file* files, int left, int right, int order);
void hoar_name(file* files, int size, int order);
void shell_name(file* files, int size, int order);