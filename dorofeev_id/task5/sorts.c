#define _CRT_SECURE_NO_WARNINGS
#define ASCENDING 1
#define DESCENDING 2
#include "sorts.h"


int comp_ascending_size(const void* a, const void* b)
{
	file* f1 = (file*)a;
	file* f2 = (file*)b;

	return f1->size - f2->size;
}

int comp_descending_size(const void* a, const void* b)
{
	file* f1 = (file*)a;
	file* f2 = (file*)b;

	return f2->size - f1->size;
}

int name_cmp(file* a, file* b)
{
	if (strcmp(a->name, b->name) >= 0)
		return 1;
	else
		return 0;
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

void hoar_size(file* files, int size, int order)
{
	if (order == ASCENDING)
	{
		qsort(files, size, sizeof(file), comp_ascending_size);
	}
	if (order == DESCENDING)
	{
		qsort(files, size, sizeof(file), comp_descending_size);
	}
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


void counting_size(file* files, int size, int order)
{
	long max = files[0].size;
	long min = files[0].size;
	for (int i = 1; i < size; i++)
	{
		if (files[i].size > max)
		{
			max = files[i].size;
		}
		if (files[i].size < min)
		{
			min = files[i].size;
		}
	}
	long range = max - min + 1;
	int* count = (int*)malloc(range * sizeof(int));
	for (int i = 0; i < range; i++)
	{
		count[i] = 0;
	}
	for (int i = 0; i < size; i++)
	{
		count[files[i].size - min]++;
	}
	for (int i = 1; i < range; i++)
	{
		count[i] += count[i - 1];
	}
	file* output = (file*)malloc(size * sizeof(file));
	if (order == ASCENDING) {
		for (int i = size - 1; i >= 0; i--)
		{
			output[count[files[i].size - min] - 1] = files[i];
			count[files[i].size - min]--;
		}
	}
	else if (order == DESCENDING)
	{
		for (int i = 0; i < size; i++)
		{
			output[size - count[files[i].size - min]] = files[i];
			count[files[i].size - min]--;
		}
	}
	for (int i = 0; i < size; i++)
	{
		files[i] = output[i];
	}
	free(count);
	free(output);
}


int comp_ascending_name(const void* a, const void* b)
{
	file* f1 = (file*)a;
	file* f2 = (file*)b;

	return name_cmp(&f1, &f2);
}

int comp_descending_name(const void* a, const void* b)
{
	file* f1 = (file*)a;
	file* f2 = (file*)b;

	return name_cmp(&f2, &f1);
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

void hoar_name(file* files, int size, int order)
{
	if (order == ASCENDING)
	{
		qsort(files, size, sizeof(file), comp_ascending_name);
	}
	if (order == DESCENDING)
	{
		qsort(files, size, sizeof(file), comp_descending_name);
	}
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
