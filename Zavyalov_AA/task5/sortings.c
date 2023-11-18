#include <stdio.h>
#include "sortings.h"
struct FileInfo {
	char name[256];
	unsigned long long size;
};

void bubble_sort(struct FileInfo* files, int size, int ascend) {
	if (ascend)
		for (int j = 0; j < size - 1; j++) {
			for (int i = size - 1; i > j; i--) {
				if (files[i].size < files[i - 1].size) {
					struct FileInfo tmp = files[i];
					files[i] = files[i - 1];
					files[i - 1] = tmp;
				}
			}
		}
	else
		for (int j = 0; j < size - 1; j++) {
			for (int i = size - 1; i > j; i--) {
				if (files[i].size > files[i - 1].size) {
					struct FileInfo tmp = files[i];
					files[i] = files[i - 1];
					files[i - 1] = tmp;
				}
			}
		}
}

void selection_sort(struct FileInfo* files, int size, int ascend) {
	if (ascend) 
		for (int i = 0; i < size - 1; i++) {
			long long min = files[i].size;
			int ind = i;
			for (int j = i + 1; j < size;  j++) {
				if (min > files[j].size) {
					min = files[j].size;
					ind = j;
				}
			}
			struct FileInfo tmp = files[ind];
			files[ind] = files[i];
			files[i] = tmp;
		}
	else 
		for (int i = 0; i < size - 1; i++) {
			long long max = files[i].size;
			int ind = i;
			for (int j = i + 1; j < size; j++) {
				if (max < files[j].size) {
					max = files[j].size;
					ind = j;
				}
			}
			struct FileInfo tmp = files[ind];
			files[ind] = files[i];
			files[i] = tmp;
		}
}

void insertion_sort(struct FileInfo* files, int size, int ascend) {
	if (ascend) {
		int j;
		for (int i = 0; i < size; i++) {
			struct FileInfo x = files[i];
			for (j = i - 1; j >= 0 && files[j].size > x.size; j--) {
				files[j + 1] = files[j];
			}
			files[j + 1] = x;
		}
	}
	else {
		int j;
		for (int i = 0; i < size; i++) {
			struct FileInfo x = files[i];
			for (j = i - 1; j >= 0 && files[j].size < x.size; j--) {
				files[j + 1] = files[j];
			}
			files[j + 1] = x;
		}
	}
}

void merge_sort(struct FileInfo* files, int size, int ascend) {

}

void sort(struct FileInfo* files, int size, int type, int ascend) {
	switch (type) {
	case 1:
		printf("Bubble sort:\n");
		bubble_sort(files, size, ascend);
		break;
	case 2:
		printf("Selection sort:\n");
		selection_sort(files, size, ascend);
		break;
	case 3:
		printf("Insertion sort:\n");
		insertion_sort(files, size, ascend);
		break;
	case 4:
		printf("Merge sort:\n");
		merge_sort(files, size, ascend);
		break;
	}
}