#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE_DIRECTORY 100

#include <stdio.h>  
#include <stdlib.h>  
#include <io.h>  
#include <time.h>
#include <string.h>
#include <memory.h>
#include <omp.h>
#include <Windows.h>
#include <wincon.h>

void bubble_sort(struct _finddata_t* a, size_t count); // 1
void select_sort(struct _finddata_t* a, size_t count); // 2
void insert_sort(struct _finddata_t* a, size_t count); // 3
void merge_sort(struct _finddata_t* a, size_t left, size_t right); // 4
void merge(struct _finddata_t* a, size_t left, size_t middle, size_t right);
void quick_sort(struct _finddata_t* a, size_t count); // 5
void shell_sort(struct _finddata_t* a, size_t count); // 6
void count_sort(struct _finddata_t* arr, size_t len); // 7
void print_file(struct _finddata_t c_file);
_fsize_t max_size(struct _finddata_t* a, size_t count);

int main()
{
    struct _finddata_t c_file;
    intptr_t hFile;
    char path[MAX_SIZE_DIRECTORY];
    double start, end;
    int count;
    char choice;
    char descend_ascend;
    char flag;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    printf("Hello! Welcome to file manager!\n");
    do
    {
        printf("Enter directory (example: \'C:\\\\temp\\\\\')\n");
            do
            {
                scanf("%s", &path);
                strcat(path, "*.*");
                if ((hFile = _findfirst(path, &c_file)) == -1L)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                    printf("This directory doesn\'t exist!\n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                }
            } while ((hFile = _findfirst(path, &c_file)) == -1L);
            printf("Choose the method of sorting:\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("1 ");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("- Bubble sort\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("2 ");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("- Select sort\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("3 ");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("- Insert sort\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("4 ");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("- Merge sort\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("5 ");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("- Quick sort\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("6 ");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("- Shell sort\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("7 ");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("- Counting sort\n");
            getchar();

            do
            {
                choice = getchar();
                if (choice < '1' || choice > '7')
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                    printf("Error!\n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                    getchar();
                }
            } while (choice < '1' || choice > '7');
            getchar();
            printf("Show files in ascending(");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("<");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf(") or descending(");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf(">");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf(") order size?\n");

            do
            {
                descend_ascend = getchar();
                if (descend_ascend != '<' && descend_ascend != '>')
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                    printf("Error!\n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                    getchar();
                }
            } while (descend_ascend != '<' && descend_ascend != '>');

            count = 0;
            do
            {
                count++;
            } while (_findnext(hFile, &c_file) == 0);
            _findclose(hFile);

            struct _finddata_t* c_file_buffer = malloc(sizeof(struct _finddata_t) * count);
            hFile = _findfirst(path, &c_file);

            for (int i = 0; i < count; i++)
            {
                _findnext(hFile, &c_file);
                c_file_buffer[i] = c_file;
            }
            _findclose(hFile);


            if (choice == '1')
            {
                start = omp_get_wtime();
                bubble_sort(c_file_buffer, count);
                end = omp_get_wtime();
            }
            if (choice == '2')
            {
                start = omp_get_wtime();
                select_sort(c_file_buffer, count);
                end = omp_get_wtime();
            }
            if (choice == '3')
            {
                start = omp_get_wtime();
                insert_sort(c_file_buffer, count);
                end = omp_get_wtime();
            }
            if (choice == '4')
            {
                start = omp_get_wtime();
                merge_sort(c_file_buffer, 0, count - 1);
                end = omp_get_wtime();
            }
            if (choice == '5')
            {
                start = omp_get_wtime();
                quick_sort(c_file_buffer, count);
                end = omp_get_wtime();
            }
            if (choice == '6')
            {
                start = omp_get_wtime();
                shell_sort(c_file_buffer, count);
                end = omp_get_wtime();
            }
            if (choice == '7')
            {
                start = omp_get_wtime();
                count_sort(c_file_buffer, count);
                end = omp_get_wtime();
            }
            getchar();
            if ((hFile = _findfirst(path, &c_file)) != -1L)
            {
                printf("\n\nFILE         DATE %24c   SIZE\n", ' ');
                printf("----         ---- %24c   ----\n", ' ');
                if (descend_ascend == '<')
                {
                    for (int i = 0; i < count; i++)
                        print_file(c_file_buffer[i]);
                }
                else
                {
                    for (int i = count - 1; i >= 0; i--)
                        print_file(c_file_buffer[i]);
                }
                printf("\nCount of files: ");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                printf("%d\n", count);
            }
            if (choice == '1')
            {
                printf("Bubble sort\n");
            }
            if (choice == '2')
            {
                printf("Select sort\n");
            }
            if (choice == '3')
            {
                printf("Insert sort\n");
            }
            if (choice == '4')
            {
                printf("Merge sort\n");
            }
            if (choice == '5')
            {
                printf("Quick sort\n");
            }
            if (choice == '6')
            {
                printf("Shell sort\n");
            }
            if (choice == '7')
            {
                printf("Counting sort\n");
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("Time for sorting: ");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("%.15f s\n", end - start);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("Do you want to continue?\n1 - yes, 0 - no\n");
            do
            {
                flag = getchar();
                if (flag != '0' && flag != '1')
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                    printf("Error!\n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                    getchar();
                }
            } while (flag != '0' && flag != '1');
            free(c_file_buffer);
            system("cls");
    } while (flag != '0');
    system("pause");
    return;
}

void bubble_sort(struct _finddata_t* a, size_t count)
{
    int i, j;
    struct _finddata_t temp;
    for (i = 0; i < count; i++)
    {
        for (j = count - 1; j > i; j--)
        {
            if (a[j - 1].size > a[j].size)
            {
                temp = a[j - 1];
                a[j - 1] = a[j];
                a[j] = temp;
            }

        }
    }
}

void select_sort(struct _finddata_t* a, size_t count)
{
    int i, j, k;
    struct _finddata_t temp;

    for (i = 0; i < count; i++)
    {
        k = i;
        temp = a[i];

        for (j = i + 1; j < count; j++)
        {
            if (a[j].size < temp.size)
            {
                k = j;
                temp = a[j];
            }
        }
        a[k] = a[i];
        a[i] = temp;
    }
}

void insert_sort(struct _finddata_t* a, size_t count)
{
    int i, j;
    struct _finddata_t temp;
    for (i = 0; i < count; i++)
    {
        temp = a[i];

        for (j = i - 1; j >= 0 && a[j].size > temp.size; j--)
            a[j + 1] = a[j];
        a[j + 1] = temp;
    }
}
void merge_sort(struct _finddata_t* a, size_t left, size_t right)
{
    int middle;
    if (left < right)
    { 

        middle = (left + right) / 2;

        merge_sort(a, left, middle); 
        merge_sort(a, middle + 1, right);
        merge(a, left, middle, right);
    }
}

void merge(struct _finddata_t* a, size_t left, size_t middle, size_t right)
{
    int pos1 = left;
    int pos2 = middle + 1;
    int pos3 = 0;
    struct _finddata_t* temp = malloc(sizeof(struct _finddata_t) * (right - left + 1));

    while (pos1 <= middle && pos2 <= right)
    {
        if (a[pos1].size < a[pos2].size)
            temp[pos3++] = a[pos1++];
        else
            temp[pos3++] = a[pos2++];
    } 
    while (pos2 <= right) 
        temp[pos3++] = a[pos2++];
    while (pos1 <= middle)
        temp[pos3++] = a[pos1++];
    for (pos3 = 0; pos3 < right - left + 1; pos3++)
        a[left + pos3] = temp[pos3];
    free(temp);
}


void quick_sort(struct _finddata_t* a, size_t count)
{

    int i = 0, j = count - 1;
    struct _finddata_t temp, p;

    p = a[count / 2];
    do {
        while (a[i].size < p.size)
            i++;
        while (a[j].size > p.size)
            j--;
        if (i <= j)
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    } while (i <= j); 
    if (j > 0)
        quick_sort(a, j);
    if (count > i)
        quick_sort(a + i, count - i);
}

void shell_sort(struct _finddata_t* a, size_t count)
{
    int i, j;
    int step;
    struct _finddata_t temp;
    for (step = count / 2; step > 0; step /= 2)
        for (i = step; i < count; i++)
        {
            temp = a[i];
            for (j = i; j >= step; j -= step)
            {
                if (temp.size < a[j - step].size)
                    a[j] = a[j - step];
                else
                    break;
            }
            a[j] = temp;
        }
}


void count_sort(struct _finddata_t* a, size_t count)
{
    int i;
    _fsize_t k = max_size(a, count);
    _fsize_t* arr_count = malloc(sizeof(int) * (k + 1));
    memset(arr_count, 0, sizeof(int) * (k + 1));
    for (i = 0; i < count; i++)
    {
        arr_count[a[i].size]++;
    }
    for (i = 1; i <= k; i++)
    {
        arr_count[i] += arr_count[i - 1];
    }
    struct _finddata_t* temp = malloc(sizeof(a[0]) * count);
    memset(temp, 0, sizeof(sizeof(a[0])) * count);
    for (i = count - 1; i >= 0; i--)
    {
        temp[arr_count[a[i].size] - 1] = a[i];
        arr_count[a[i].size]--;
    }
    for (i = 0; i < count; i++)
    {
        a[i] = temp[i];
    }
    free(arr_count);
    free(temp);
}


_fsize_t max_size(struct _finddata_t* a, size_t count)
{
    size_t max = 0;
    for (int i = 0; i < count; i++)
    {
        if (max < a[i].size)
            max = a[i].size;
    }
    return max;
}

void print_file(struct _finddata_t a)
{
    char buffer[30];
    ctime_s(buffer, _countof(buffer), &a.time_write);
    printf("%-12.12s %.24s  %10ld\n", a.name, buffer, a.size);
}

