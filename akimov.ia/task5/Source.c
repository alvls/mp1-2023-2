#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#include <omp.h>

void bubble_sort(struct _finddata_t* arr, int size)
{
    int i, j;
    struct _finddata_t temp;
    for (i = 0; i < size; i++)
    {
        for (j = size - 1; j > i; j--)
            if (arr[j - 1].size > arr[j].size)
            {
                temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;
            }
    }
}

void selection_sort(struct _finddata_t* arr, int size)
{
    int i, j, min_index;
    struct _finddata_t temp;
    for (i = 0; i < size; i++)
    {
        min_index = i;
        for (j = i + 1; j < size; j++)
            if (arr[j].size < arr[min_index].size)
                min_index = j;
        temp = arr[min_index];
        arr[min_index] = arr[i];
        arr[i] = temp;
    }
}

void insertion_sort(struct _finddata_t* arr, int size)
{
    int i, j;
    struct _finddata_t temp;
    for (i = 0; i < size; i++)
    {
        temp = arr[i];
        for (j = i - 1; j >= 0 && arr[j].size > temp.size; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = temp;
    }
}

void merge(struct _finddata_t* arr, int left, int mid, int right)
{
    int i, j, g, size = right - left + 1;
    i = left;
    j = mid + 1;
    g = 0;
    struct _finddata_t* temp = malloc(size * sizeof(struct _finddata_t));
    while (i <= mid && j <= right)
    {
        if (arr[i].size < arr[j].size)
            temp[g++] = arr[i++];
        else
            temp[g++] = arr[j++];
    }
    while (j <= right)
        temp[g++] = arr[j++];
    while (i <= mid)
        temp[g++] = arr[i++];
    for (g = 0; g < size; g++)
        arr[left + g] = temp[g];
    free(temp);
}

void merge_sort(struct _finddata_t* arr, int left, int right)
{
    int mid = (left + right) / 2;
    if (left == right)
        return;
    if (left < right)
    {
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void quick_sort(struct _finddata_t* arr, int size)
{
    int i = 0, j = size - 1;
    struct _finddata_t temp, p;
    p = arr[size / 2];
    do
    {
        while (arr[i].size < p.size)
            i++;
        while (arr[j].size > p.size)
            j--;
        if (i <= j)
        {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    } while (i <= j);
    if (j > 0)
        quick_sort(arr, j);
    if (i < size)
        quick_sort(arr + i, size - i);
}

int increment(int* arr, int size)
{
    int p1, p2, p3, s;
    p1 = p2 = p3 = 1;
    s = -1;
    do
    {
        if (++s % 2)
            arr[s] = 8 * p1 - 6 * p2 + 1;
        else
        {
            arr[s] = 9 * p1 - 9 * p3 + 1;
            p2 *= 2;
            p3 *= 3;
        }
        p1 *= 2;
    } while (3 * arr[s] < size);
    return s > 0 ? --s : 0;
}

void shell_sort(struct _finddata_t* arr, int size)
{
    struct _finddata_t temp;
    int inc, i, j, s, * seq;
    seq = (int*)malloc(size * sizeof(int));
    s = increment(seq, size);
    while (s >= 0)
    {
        inc = seq[s--];
        for (i = inc;i < size;i++)
        {
            temp = arr[i];
            for (j = i - inc; (j >= 0) && (arr[j].size > temp.size); j -= inc)
                arr[j + inc] = arr[j];
            arr[j + inc] = temp;
        }
    }
    free(seq);
}

void counting_sort(struct _finddata_t* arr, int size)
{
    long int max_el = 0, min_el = arr[0].size;
    int k = 0, size_of_count;
    struct _finddata_t* copy = (struct _finddata_t*)malloc(size * sizeof(struct _finddata_t));
    for (int i = 0; i < size; i++)
    {
        if (arr[i].size <= min_el)
            min_el = arr[i].size;
        if (arr[i].size >= max_el)
            max_el = arr[i].size;
        copy[i] = arr[i];
    }
    size_of_count = max_el - min_el + 1;
    long int* c = (long int*)malloc(size_of_count * sizeof(long int));
    memset(c, 0, size_of_count * sizeof(long int));
    for (int i = 0; i < size; i++)
        c[arr[i].size - min_el]++;
    for (int i = 0; i < size_of_count; i++)
    {
        while (c[i] > 0)
        {
            for (int j = 0; j < size; j++)
                if (min_el + i == copy[j].size)
                {
                    arr[k++] = copy[j];
                    c[i]--;
                    break;
                }
        }
    }
    free(copy);
    free(c);
}

void main()
{
    setlocale(LC_ALL, "rus");
    struct _finddata_t c_file;
    struct _finddata_t* sort;
    intptr_t hFile;
    char path[200];
    int flag = 1, sort_type, sorting_method, another_sort_type;
    double start_time = 0, end_time = 0;
    system("chcp 1251");
    while (flag)
    {
        int count = 0;
        system("cls");
        do
        {
            printf("������� ���� �� ��������� ��������: ");
            scanf("%s", path);
            system("cls");
            strcat_s(path, 200, "\\*.*");
            flag = 0;
            if ((hFile = _findfirst(path, &c_file)) == -1L)
            {
                printf("� ������� �������� ��� ������!\n");
                flag = 1;
            }
        } while (flag);
        system("cls");
        do
        {
            count++;
        } while (_findnext(hFile, &c_file) == 0);
        sort = (struct _finddata_t*)malloc(count * sizeof(struct _finddata_t));
        hFile = _findfirst(path, &c_file);
        int kol = 0;
        do
        {
            if (kol < count)
            {
                sort[kol] = c_file;
                kol++;
            }
        } while (_findnext(hFile, &c_file) == 0);
        _findclose(hFile);
        flag = 1;
        while (flag)
        {
            do
            {
                printf("\t������ ����������:\n1.���������� ���������\n2.���������� �������\n3.���������� ���������\n4.���������� ��������\n"
                    "5.���������� �����\n6.���������� �����\n7.���������� ���������\n������� ����� ���������� ������ ����������: ");
                scanf("%d", &sort_type);
                system("cls");
                flag = 0;
                while (getchar() != '\n');
                if (sort_type < 1 || sort_type > 7)
                {
                    printf("�� ����� ������������ ����� ����������!\n");
                    flag = 1;
                }
            } while (flag);
            switch (sort_type)
            {
            case 1:
                start_time = omp_get_wtime();
                bubble_sort(sort, count);
                end_time = omp_get_wtime();
                break;
            case 2:
                start_time = omp_get_wtime();
                selection_sort(sort, count);
                end_time = omp_get_wtime();
                break;
            case 3:
                start_time = omp_get_wtime();
                insertion_sort(sort, count);
                end_time = omp_get_wtime();
                break;
            case 4:
                start_time = omp_get_wtime();
                merge_sort(sort, 0, count - 1);
                end_time = omp_get_wtime();
                break;
            case 5:
                start_time = omp_get_wtime();
                quick_sort(sort, count);
                end_time = omp_get_wtime();
                break;
            case 6:
                start_time = omp_get_wtime();
                shell_sort(sort, count);
                end_time = omp_get_wtime();
                break;
            case 7:
                start_time = omp_get_wtime();
                counting_sort(sort, count);
                end_time = omp_get_wtime();
                break;
            }
            do
            {
                printf("\t������� ����������:\n1.�� �����������\n2.�� ��������\n������� ����� ���������� ������� ����������: ");
                scanf("%d", &sorting_method);
                system("cls");
                flag = 0;
                while (getchar() != '\n');
                if (sorting_method != 1 && sorting_method != 2)
                {
                    printf("�� ����� ������������ ����� ����������!\n");
                    flag = 1;
                }
            } while (flag);
            if (sorting_method == 1)
            {
                printf("������� ���������� ����������: %s\n\n", path);
                printf("FILE                           DATE %24c   SIZE\n", ' ');
                printf("----                           ---- %24c   ----\n", ' ');
                for (int i = 0; i < count; i++)
                {
                    char buffer[30];
                    ctime_s(buffer, _countof(buffer), &sort[i].time_write);
                    printf("%-30.30s %.24s  %10ld\n", sort[i].name, buffer, sort[i].size);
                }
                printf("\n����� ����������: %lf ���\n", end_time - start_time);
            }
            else
            {
                printf("������� ���������� ����������: %s\n\n", path);
                printf("FILE                           DATE %24c   SIZE\n", ' ');
                printf("----                           ---- %24c   ----\n", ' ');
                for (int i = count - 1; i >= 0; i--)
                {
                    char buffer[30];
                    ctime_s(buffer, _countof(buffer), &sort[i].time_write);
                    printf("%-30.30s %.24s  %10ld\n", sort[i].name, buffer, sort[i].size);
                }
                printf("\n����� ����������: %lf ���\n", end_time - start_time);
            }
            do
            {
                printf("������ ������������� ������ �������?(1 - ��, 0 - ���): ");
                scanf("%d", &another_sort_type);
                flag = 0;
                while (getchar() != '\n');
                if (another_sort_type != 0 && another_sort_type != 1)
                    flag = 1;
            } while (flag);
            if (another_sort_type == 1)
            {
                flag = 1;
                system("cls");
            }
        }
        free(sort);
        system("cls");
    }
    system("pause");
}