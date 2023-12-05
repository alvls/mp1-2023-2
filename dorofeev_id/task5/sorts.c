#define _CRT_SECURE_NO_WARNINGS
#define ASCENDING 1
#define DESCENDING 2
#define MAX_FILE_SIZE 3000000000
#include "sorts.h"


int name_cmp(const wchar_t* a, const wchar_t* b) {
	return wcscmp(a, b);
}

int size_cmp(const long a, const long b, int order) {
	return (order == 1) ? (a - b) : (b - a);
}

void swap(file* a, file* b)
{
	file tmp = *a;
	*a = *b;
	*b = tmp;
}

void bubble_size(file* files, int amount, int order)
{
	for (int i = 0; i < amount - 1; i++)
	{
		for (int j = 0; j < amount - i - 1; j++)
		{
			if (order == ASCENDING) //ascending
			{
				if (files[j].size > files[j + 1].size)
				{
					swap(&files[j], &files[j + 1]);
				}
			}
			else if (order == DESCENDING) //descending
			{
				if (files[j].size < files[j + 1].size)
				{
					swap(&files[j], &files[j + 1]);
				}
			}
		}
	}
}

void selection_size(file* files, int amount, int order)
{
	for (int i = 0; i < amount - 1; i++)
	{
		int min_index = i;
		for (int j = i + 1; j < amount; j++)
		{
			if (order == ASCENDING)
			{
				if (files[j].size < files[min_index].size)
				{
					min_index = j;
				}
			}
			else if (order == DESCENDING)
			{
				if (files[j].size > files[min_index].size)
				{
					min_index = j;
				}
			}
		}
		if (min_index != i)
		{
			swap(&files[i], &files[min_index]);
		}
	}
}

void insertion_size(file* files, int amount, int order)
{
	for (int i = 1; i < amount; i++)
	{
		file key = files[i];
		int j = i - 1;
		if (order == ASCENDING)
		{
			while (j >= 0 && files[j].size > key.size)
			{
				files[j + 1] = files[j];
				j--;
			}
		}
		else if (order == DESCENDING)
		{
			while (j >= 0 && files[j].size < key.size)
			{
				files[j + 1] = files[j];
				j--;
			}
		}
		files[j + 1] = key;
	}
}


void merge_size(file* files, int left, int middle, int right, int order)
{
	int n1 = middle - left + 1;
	int n2 = right - middle;
	file* L = (file*)malloc(n1 * sizeof(file));
	file* R = (file*)malloc(n2 * sizeof(file));
	for (int i = 0; i < n1; i++)
	{
		L[i] = files[left + i];
	}
	for (int j = 0; j < n2; j++)
	{
		R[j] = files[middle + 1 + j];
	}
	int i = 0;
	int j = 0;
	int k = left;
	if (order == ASCENDING)
	{
		while (i < n1 && j < n2)
		{
			if (L[i].size <= R[j].size)
			{
				files[k] = L[i];
				i++;
			}
			else
			{
				files[k] = R[j];
				j++;
			}
			k++;
		}
	}
	else if (order == DESCENDING)
	{
		while (i < n1 && j < n2)
		{
			if (L[i].size >= R[j].size)
			{
				files[k] = L[i];
				i++;
			}
			else
			{
				files[k] = R[j];
				j++;
			}
			k++;
		}
	}
	while (i < n1)
	{
		files[k] = L[i];
		i++;
		k++;
	}
	while (j < n2)
	{
		files[k] = R[j];
		j++;
		k++;
	}

	free(L);
	free(R);
}


void merge_sort_size(file* files, int left, int right, int order)
{
	if (left < right)
	{
		int middle = (left + right) / 2;
		merge_sort_size(files, left, middle, order);
		merge_sort_size(files, middle + 1, right, order);
		merge_size(files, left, middle, right, order);
	}
}

int partition_size(file* files, int low, int high, int order) 
{
	long pivot = files[high].size;
	int i = low - 1;

	for (int j = low; j <= high - 1; j++) 
	{
		if (size_cmp(files[j].size, pivot, order) < 0) 
		{
			i++;
			swap(&files[i], &files[j]);
		}
	}

	swap(&files[i + 1], &files[high]);
	return i + 1;
}

void hoar_size(file* files, int size, int order)
{
	int* stack = (int*)malloc(size * sizeof(int));
	int top = -1;

	stack[++top] = 0;
	stack[++top] = size - 1;

	while (top >= 0) 
	{
		int h = stack[top--];
		int l = stack[top--];

		int p = partition_size(files, l, h, order);

		if (p - 1 > l) 
		{
			stack[++top] = l;
			stack[++top] = p - 1;
		}

		if (p + 1 < h) 
		{
			stack[++top] = p + 1;
			stack[++top] = h;
		}
	}

	free(stack);
}

void shell_size(file* files, int size, int order)
{
	int gap = size / 2;
	while (gap > 0)
	{
		for (int i = gap; i < size; i++)
		{
			file temp = files[i];
			int j = i;
			if (order == ASCENDING)
			{
				while (j >= gap && files[j - gap].size > temp.size)
				{
					files[j] = files[j - gap];
					j -= gap;
				}
			}
			else if (order == DESCENDING)
			{
				while (j >= gap && files[j - gap].size < temp.size)
				{
					files[j] = files[j - gap];
					j -= gap;
				}
			}
			files[j] = temp;
		}
		gap /= 2;
	}
}


void counting_size(file* files, int size, int order) {
	if (size <= 0) {
		// Обработка случая, когда массив пуст или имеет неположительный размер
		return;
	}

	long max = files[0].size;
	long min = files[0].size;

	// Находим максимальный и минимальный размер файлов
	for (int i = 1; i < size; i++) {
		if (files[i].size > max) {
			max = files[i].size;
		}
		if (files[i].size < min) {
			min = files[i].size;
		}
	}

	// Ограничиваем максимальный размер файла до MAX_FILE_SIZE
	max = (max > MAX_FILE_SIZE) ? MAX_FILE_SIZE : max;

	// Вычисляем новый диапазон размеров файлов
	unsigned long long range = max - min + 1;

	// Выделяем память для массива count
	unsigned long long* count = (unsigned long long*)malloc(range * sizeof(unsigned long long));

	if (count == NULL) {
		// Обработка случая, когда malloc завершился неудачно
		return;
	}

	// Инициализируем массив count
	for (int i = 0; i < range; i++) {
		count[i] = 0;
	}

	// Считаем количество файлов для каждого размера
	for (int i = 0; i < size; i++) {
		count[files[i].size - min]++;
	}

	// Обновляем массив count для хранения кумулятивных сумм
	for (int i = 1; i < range; i++) {
		count[i] += count[i - 1];
	}

	// Выделяем память для массива output
	file* output = (file*)malloc(size * sizeof(file));

	if (order == ASCENDING) {
		// Сортируем файлы в порядке возрастания
		for (int i = size - 1; i >= 0; i--) {
			output[count[files[i].size - min] - 1] = files[i];
			count[files[i].size - min]--;
		}
	}
	else if (order == DESCENDING) {
		// Сортируем файлы в порядке убывания
		for (int i = 0; i < size; i++) {
			output[size - count[files[i].size - min]] = files[i];
			count[files[i].size - min]--;
		}
	}

	// Копируем отсортированный результат обратно в исходный массив
	for (int i = 0; i < size; i++) {
		files[i] = output[i];
	}

	// Освобождаем выделенную память
	free(count);
	free(output);
}


void bubble_name(file* files, int amount, int order)
{
	for (int i = 0; i < amount - 1; i++)
	{
		for (int j = 0; j < amount - i - 1; j++)
		{
			if (order == ASCENDING) //ascending
			{
				if (name_cmp(&files[j], &files[j + 1]) == 1)
				{
					swap(&files[j], &files[j + 1]);
				}
			}
			else if (order == DESCENDING) //descending
			{
				if (name_cmp(&files[j], &files[j + 1]) == 0)
				{
					swap(&files[j], &files[j + 1]);
				}
			}
		}
	}
}

void selection_name(file* files, int amount, int order)
{
	for (int i = 0; i < amount - 1; i++)
	{
		int min_index = i;
		for (int j = i + 1; j < amount; j++)
		{
			if (order == ASCENDING)
			{
				if (name_cmp(&files[j], &files[min_index]) == 0)
				{
					min_index = j;
				}
			}
			else if (order == DESCENDING)
			{
				if (name_cmp(&files[j], &files[min_index]) == 1)
				{
					min_index = j;
				}
			}
		}
		if (min_index != i)
		{
			swap(&files[i], &files[min_index]);
		}
	}
}

void insertion_name(file* files, int amount, int order)
{
	for (int i = 1; i < amount; i++)
	{
		file key = files[i];
		int j = i - 1;
		if (order == ASCENDING)
		{
			while (j >= 0 && name_cmp(&files[j], &key) == 1)
			{
				files[j + 1] = files[j];
				j--;
			}
		}
		else if (order == DESCENDING)
		{
			while (j >= 0 && name_cmp(&files[j], &key) == 0)
			{
				files[j + 1] = files[j];
				j--;
			}
		}
		files[j + 1] = key;
	}
}

void merge_name(file* files, int left, int middle, int right, int order)
{
	int n1 = middle - left + 1;
	int n2 = right - middle;
	file* L = (file*)malloc(n1 * sizeof(file));
	file* R = (file*)malloc(n2 * sizeof(file));
	for (int i = 0; i < n1; i++)
	{
		L[i] = files[left + i];
	}
	for (int j = 0; j < n2; j++)
	{
		R[j] = files[middle + 1 + j];
	}
	int i = 0;
	int j = 0;
	int k = left;
	if (order == ASCENDING)
	{
		while (i < n1 && j < n2)
		{
			if (name_cmp(&L[i], &R[j]) == 0)
			{
				files[k] = L[i];
				i++;
			}
			else
			{
				files[k] = R[j];
				j++;
			}
			k++;
		}
	}
	else if (order == DESCENDING)
	{
		while (i < n1 && j < n2)
		{
			if (name_cmp(&L[i], &R[j]) == 1)
			{
				files[k] = L[i];
				i++;
			}
			else
			{
				files[k] = R[j];
				j++;
			}
			k++;
		}
	}
	while (i < n1)
	{
		files[k] = L[i];
		i++;
		k++;
	}
	while (j < n2)
	{
		files[k] = R[j];
		j++;
		k++;
	}

	free(L);
	free(R);
}

void merge_sort_name(file* files, int left, int right, int order)
{
	if (left < right)
	{
		int middle = (left + right) / 2;
		merge_sort_name(files, left, middle, order);
		merge_sort_name(files, middle + 1, right, order);
		merge_name(files, left, middle, right, order);
	}
}

int partition_name(file* files, int low, int high) 
{
	wchar_t pivot[256];
	wcscpy(pivot, files[high].name);
	int i = low - 1;

	for (int j = low; j <= high - 1; j++) 
	{
		if (name_cmp(files[j].name, pivot) < 0) 
		{
			i++;
			swap(&files[i], &files[j]);
		}
	}

	swap(&files[i + 1], &files[high]);
	return i + 1;
}

void hoar_name(file* files, int size, int order)
{
	int* stack = (int*)malloc(size * sizeof(int));
	int top = -1;

	stack[++top] = 0;
	stack[++top] = size - 1;

	while (top >= 0) 
	{
		int h = stack[top--];
		int l = stack[top--];

		int p = partition_name(files, l, h);

		if (p - 1 > l) 
		{
			stack[++top] = l;
			stack[++top] = p - 1;
		}

		if (p + 1 < h) 
		{
			stack[++top] = p + 1;
			stack[++top] = h;
		}
	}

	free(stack);
}

void shell_name(file* files, int size, int order)
{
	int gap = size / 2;
	while (gap > 0)
	{
		for (int i = gap; i < size; i++)
		{
			file temp = files[i];
			int j = i;
			if (order == ASCENDING)
			{
				while (j >= gap && (name_cmp(&files[j - gap], &temp) == 1))
				{
					files[j] = files[j - gap];
					j -= gap;
				}
			}
			else if (order == DESCENDING)
			{
				while (j >= gap && (name_cmp(&files[j - gap], &temp) == 0))
				{
					files[j] = files[j - gap];
					j -= gap;
				}
			}
			files[j] = temp;
		}
		gap /= 2;
	}
}
