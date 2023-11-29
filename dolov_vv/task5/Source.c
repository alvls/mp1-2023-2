#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h> 
#include <time.h>
#include <io.h> 
#include <malloc.h>
#include <omp.h>
#include <string.h>


void bubleSort(int a[], int size) {
	int x, j;
	for (int i = 0; i < size - 1; i++) {
		for (j = size - 1; j > i; j--) {
			if (a[j - 1] > a[j]) {
				x = a[j-1];
				a[j-1] = a[j];
				a[j] = x;
			}
		}
	}
}

void selectSort(int a[], int size) {
	int i, j, k;
	int x;
	for (i = 0; i < size; i++) {
		k = i; 
		x = a[i];
		for (j = i + 1; j < size; j++) {
			if (a[j] < x) {
				k = j; 
				x = a[j];
			}
		}
		a[k] = a[i]; 
		a[i] = x;
	}
}

void insertSort(int a[], int size) {
	int x;
	int i, j;
	for (i = 0; i < size; i++) {
		x = a[i];
		for (j = i - 1; j >= 0 && a[j] > x; j--)
			a[j + 1] = a[j];
		a[j + 1] = x;
	}
}


void merge(int a[], long lb, long split, long ub) {
	long pos1 = lb;
	long pos2 = split + 1;
	long pos3 = 0;

	int* temp = (int*)malloc((ub - lb + 1) * sizeof(int));

	while (pos1 <= split && pos2 <= ub) {
		if (a[pos1] < a[pos2])
			temp[pos3++] = a[pos1++];
		else
			temp[pos3++] = a[pos2++];
	}

	while (pos2 <= ub)
		temp[pos3++] = a[pos2++];

	while (pos1 <= split)
		temp[pos3++] = a[pos1++];

	for (pos3 = 0; pos3 < ub - lb + 1; pos3++)
		a[lb + pos3] = temp[pos3];

	free(temp);
}
void mergeSort(int a[], long lb, long ub) {
	if (lb < ub) {
		long split = (lb + ub) / 2;

		mergeSort(a, lb, split);
		mergeSort(a, split + 1, ub);
		merge(a, lb, split, ub);
	}
}

void quickSort(int* numbers, int left, int right)
{
	int pivot;
	int l_hold = left;
	int r_hold = right;
	pivot = numbers[left];
	while (left < right)
	{
		while ((numbers[right] >= pivot) && (left < right))
			right--;
		if (left != right)
		{
			numbers[left] = numbers[right];
			left++;
		}
		while ((numbers[left] <= pivot) && (left < right))
			left++;
		if (left != right)
		{
			numbers[right] = numbers[left];
			right--;
		}
	}
	numbers[left] = pivot;
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot)
		quickSort(numbers, left, pivot - 1);
	if (right > pivot)
		quickSort(numbers, pivot + 1, right);
}


int increment(long inc[], long size) {
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
}
void shellSort(int a[], long size) {
	long inc, i, j, seq[40];
	int s;
	s = increment(seq, size);
	while (s >= 0) {
		inc = seq[s--];
		for (i = inc; i < size; i++) {
			int temp = a[i];
			for (j = i - inc; (j >= 0) && (a[j] > temp); j -= inc)
				a[j + inc] = a[j];
			a[j + inc] = temp;
		}
	}
}


void countingSort(int* array, int n) {
	int i;
	int maxValue = array[0];
	int minValue = array[0];
	for (i = 1; i < n; ++i) {
		if (array[i] > maxValue) maxValue = array[i];
		if (array[i] < minValue) minValue = array[i];
	}
	int k = maxValue - minValue + 1; 
	int* counts = (int*)malloc(k * sizeof(int));
	memset(counts, 0, k * sizeof(int));
	for (i = 0; i < n; ++i) {
		counts[array[i] - minValue]++;
	}
	int idx = 0;
	for (i = 0; i < k; ++i) {
		while (counts[i] > 0) {
			array[idx++] = i + minValue;
			counts[i]--;
		}
	}
	free(counts);
}


void reverse(int a[], int size) {
	int tmp;
	for (int i = 0; i < (size / 2); i++) {
		tmp = a[i];
		a[i] = a[size - i - 1];
		a[size - i - 1] = tmp;
	}
}


void print_to_screen(int a[], int size, char path[]) {
	struct _finddata_t c_file;
	intptr_t hFile;

	if ((hFile = _findfirst(path, &c_file)) == -1L)
		printf("В данном дериктории нет файлов\n");
	else
	{
		do {
			if (a[0] == c_file.size && strcmp(c_file.name, ".") != 0 && strcmp(c_file.name, "..") != 0) {
				printf("%-20.20s  - %10ld байт\n", c_file.name, c_file.size);
			}
		} while (_findnext(hFile, &c_file) == 0);
		_findclose(hFile);
	}
	for (int i = 1; i < size; i++) {
		if (a[i] != a[i - 1]) {
			if ((hFile = _findfirst(path, &c_file)) == -1L)
				printf("В данном директории нет файлов\n");
			else
			{
				do {
					if (a[i] == c_file.size && strcmp(c_file.name, ".") != 0 && strcmp(c_file.name, "..") != 0) {
						printf("%-20.20s  - %10ld байт\n", c_file.name, c_file.size);
					}
				} while (_findnext(hFile, &c_file) == 0);
				_findclose(hFile);
			}
		}
	}
}

int check_files_exist(const char* path) {
	struct _finddata_t c_file;
	intptr_t hFile;
	if ((hFile = _findfirst(path, &c_file)) == -1L) {
		return 0;
	}
	else {
		_findclose(hFile);
		return 1;
	}
}


void main() {
	setlocale(LC_ALL, "Russian");
	struct _finddata_t c_file;
	intptr_t hFile;
	char path[200];
	double start = 0, end = 0;
	int num = 0;
	int asc_des = 0;
	int size = 0;
	int count = 0;
	printf("Введите адрес директории, в которой хотите отсортировать содержимое\n");
	printf("Вид ввода(как пример): c:\\temp\\*.* \n");
	gets(path);
	if ((hFile = _findfirst(path, &c_file)) == -1L)
		printf("В данном дериктории нет файлов\n");
	else
	{
		do {
			size += 1;
		} while (_findnext(hFile, &c_file) == 0);
		_findclose(hFile);
	}

	size = size - 2;  // учитываем что есть файлы "." и ".."
	int* a = (int*)malloc(size*sizeof(struct _finddata_t));
	int max = -100000;
	for (int i = 0; i < size; i++) {
		if (a[i] > max)
			max = a[i];
	}
	int filesExist = check_files_exist(path);
	int wa = 1;
	while (wa) {
		count = 0;
		if ((hFile = _findfirst(path, &c_file)) != -1L) 
		{
			count = 0;
			do {
				count += 1;
				if (count > 2) {
					a[count - 3] = c_file.size;
				}
			} while (_findnext(hFile, &c_file) == 0);
			_findclose(hFile);
		}
		if (filesExist)
		{
			printf("Какую сортировку вы хотели бы использовать?\n");
			printf("Введите 1, чтобы использовать сортировку пузырьком \n");
			printf("Введите 2, чтобы использовать сортировку выбором \n");
			printf("Введите 3, чтобы использовать сортировку вставками \n");
			printf("Введите 4, чтобы использовать сортировку слиянием \n");
			printf("Введите 5, чтобы использовать сортировку Хоара \n");
			printf("Введите 6, чтобы использовать сортировку Шелла \n");
			printf("Введите 7, чтобы использовать сортировку подсчетом \n");
			printf("Если же вы хотите закончить введите 0\n");
			scanf_s("%i", &num);

			if (num != 0)
			{
				printf("Введите 0, если хотите использовать сортировку по возрастанию\n");
				printf("Введите 1, если хотите использовать сортировку по убыванию\n");
				scanf_s("%i", &asc_des);
			}
		}
		else 
		{
			num = 0;
		}

		switch (num) {
		case 0:
			wa = 0;
			break;
		case 1:
			start = omp_get_wtime();
			bubleSort(a, size, path);
			end = omp_get_wtime();
			if (asc_des == 0) {
				print_to_screen(a, size, path);
				printf("Время выполнения выбранной вами сортировки: %lf сек.\n", end - start);
				printf("\n");
			}
			if (asc_des == 1) {
				reverse(a, size);
				print_to_screen(a, size, path);
				printf("Время выполнения выбранной вами сортировки: %lf сек.\n", end - start);
				printf("\n");
			}
			break;
		case 2:
			start = omp_get_wtime();
			selectSort(a, size, path);
			end = omp_get_wtime();
			if (asc_des == 0) {
				print_to_screen(a, size, path);
				printf("Время выполнения выбранной вами сортировки: %lf сек.\n", end - start);
				printf("\n");
			}
			if (asc_des == 1) {
				reverse(a, size);
				print_to_screen(a, size, path);
				printf("Время выполнения выбранной вами сортировки: %lf сек.\n", end - start);
				printf("\n");
			}
			break;
		case 3:
			start = omp_get_wtime();
			insertSort(a, size, path);
			end = omp_get_wtime();
			if (asc_des == 0) {
				print_to_screen(a, size, path);
				printf("Время выполнения выбранной вами сортировки: %lf сек.\n", end - start);
				printf("\n");
			}
			if (asc_des == 1) {
				reverse(a, size);
				print_to_screen(a, size, path);
				printf("Время выполнения выбранной вами сортировки: %lf сек.\n", end - start);
				printf("\n");
			}
			break;
		case 4:
			start = omp_get_wtime();
			mergeSort(a, 0, size - 1);
			end = omp_get_wtime();
			if (asc_des == 0) {
				print_to_screen(a, size, path);
				printf("Время выполнения выбранной вами сортировки: %lf сек.\n", end - start);
				printf("\n");
			}
			if (asc_des == 1) {
				reverse(a, size);
				print_to_screen(a, size, path);
				printf("Время выполнения выбранной вами сортировки: %lf сек.\n", end - start);
				printf("\n");
			}
			break;
		case 5:
			start = omp_get_wtime();
			quickSort(a, 0, size - 1);
			end = omp_get_wtime();
			if (asc_des == 0) {
				print_to_screen(a, size, path);
				printf("Время выполнения выбранной вами сортировки: %lf сек.\n", end - start);
				printf("\n");
			}
			if (asc_des == 1) {
				reverse(a, size);
				print_to_screen(a, size, path);
				printf("Время выполнения выбранной вами сортировки: %lf сек.\n", end - start);
				printf("\n");
			}
			break;
		case 6:
			start = omp_get_wtime();
			shellSort(a, size);
			end = omp_get_wtime();
			if (asc_des == 0) {
				print_to_screen(a, size, path);
				printf("Время выполнения выбранной вами сортировки: %lf сек.\n", end - start);
				printf("\n");
			}
			if (asc_des == 1) {
				reverse(a, size);
				print_to_screen(a, size, path);
				printf("Время выполнения выбранной вами сортировки: %lf сек.\n", end - start);
				printf("\n");
			}
			break;
		case 7:
			start = omp_get_wtime();
			countingSort(a, size, max);
			end = omp_get_wtime();
			if (asc_des == 0) {
				print_to_screen(a, size, path);
				printf("Время выполнения выбранной вами сортировки: %lf сек.\n", end - start);
				printf("\n");
			}
			if (asc_des == 1) {
				reverse(a, size);
				print_to_screen(a, size, path);
				printf("Время выполнения выбранной вами сортировки: %lf сек.\n", end - start);
				printf("\n");
			}
			break;
		}
	}
	free(a);
	system("pause");
}