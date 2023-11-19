#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sortings.h"
struct FileInfo {
	wchar_t name[256];
	unsigned long long size;
};

void bubbleSort(struct FileInfo* files, int size, int ascend) {
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

void selectionSort(struct FileInfo* files, int size, int ascend) {
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

void insertionSort(struct FileInfo* files, int size, int ascend) {
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

void mergeSort(struct FileInfo* files, int ascend, int lb, int ub) {
	int split = (lb + ub) / 2;
	if (lb < ub) {
		mergeSort(files, ascend, lb, split);
		mergeSort(files, ascend, split + 1, ub);
	}
	merge(files, ascend, lb, split, ub);

}

void merge(struct FileInfo* files, int ascend, int lb, int split, int ub) {
	int pos1 = lb;
	int pos2 = split + 1;
	int pos3 = 0;
	struct FileInfo* T = malloc((ub - lb + 1) * sizeof(struct FileInfo));
	if (ascend) 
		while (pos1 <= split && pos2 <= ub) {
			if (files[pos1].size < files[pos2].size)
				T[pos3++] = files[pos1++];
			else
				T[pos3++] = files[pos2++];
		}
	else
		while (pos1 <= split && pos2 <= ub) {
			if (files[pos1].size > files[pos2].size)
				T[pos3++] = files[pos1++];
			else
				T[pos3++] = files[pos2++];
		}
	while (pos1 <= split) {
		T[pos3++] = files[pos1++];
	}
	while (pos2 <= ub) {
		T[pos3++] = files[pos2++];
	}
	for (int i = lb; i <= ub; i++) {
		files[i] = T[i - lb];
	}
	free(T);
}

void quickSort(struct FileInfo* files, int n, int ascend) {
	int i = 0, j = n - 1;
	struct FileInfo temp;
	unsigned long long p = files[n >> 1].size;

	do {
		while (files[i].size < p) i++;
		while (files[j].size > p) j--;

		if (i <= j) {
			temp = files[i], files[i] = files[j], files[j] = temp;
			i++; j--;
		}
	} while (i <= j);

	if (j > 0) quickSort(files, j, ascend);
	if (n > i) quickSort(files + i, n - i, ascend);
}

/*int increment(long inc[], long size) {
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
} */

void shellSort(struct FileInfo* files, int size, int ascend) {
	int inc = size / 2;
	if (ascend)
		while (inc) {
			for (int i = 0; i < size; i++) {
				int tmp = i;
				while (tmp >= inc && files[tmp - inc].size > files[tmp].size) {
					struct FileInfo temp = files[tmp - inc];
					files[tmp - inc] = files[tmp];
					files[tmp] = temp;
					tmp -= inc;
				}
			}
			if (inc == 2)
				inc = 1;
			else
				inc = (inc * 5 / 11);
		}
	else
		while (inc) {
			for (int i = 0; i < size; i++) {
				int tmp = i;
				while (tmp >= inc && files[tmp - inc].size < files[tmp].size) {
					struct FileInfo temp = files[tmp - inc];
					files[tmp - inc] = files[tmp];
					files[tmp] = temp;
					tmp -= inc;
				}
			}
			if (inc == 2)
				inc = 1;
			else
				inc = (inc * 5 / 11);
		}
}

void sort(struct FileInfo* files, int size, int type, int ascend) {
	switch (type) {
	case 1:
		wprintf(L"Bubble sort:\n");
		bubbleSort(files, size, ascend);
		break;
	case 2:
		wprintf(L"Selection sort:\n");
		selectionSort(files, size, ascend);
		break;
	case 3:
		wprintf(L"Insertion sort:\n");
		insertionSort(files, size, ascend);
		break;
	case 4:
		wprintf(L"Merge sort:\n");
		mergeSort(files, ascend, 0, size - 1);
		break;
	case 5: // TODO
		wprintf(L"Quick sort:\n");
		quickSort(files, size - 1, ascend);
		break;
	case 6:
		wprintf(L"Shell sort:\n");
		shellSort(files, size, ascend);
		break;
	}
}