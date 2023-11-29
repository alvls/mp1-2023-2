#define _CRT_SECURE_NO_WARNINGS
#define STR_(X) #X
#define STR(X) STR_(X)
#define strdup _strdup
#define MAX_PATH_LENGTH 511

#include <stdio.h>  
#include <stdlib.h> 
#include <string.h>
#include <locale.h>
#include <memory.h>
#include <io.h>  
#include <time.h>
#include <Windows.h>

// ������ ��������� � ����������� � �����, ��� ����� �������� ��������, ���� � ������.
typedef struct
{
    char* name;
    time_t time_write;
    _fsize_t size;
} file_info;

// �������� ���������� ������ � ����.
size_t count_files(const char* path)
{
    struct _finddata_t c_file;
    intptr_t hFile;
    size_t count = 0;
    if ((hFile = _findfirst(path, &c_file)) == -1L)
        return 0;
    else
    {
        do
        {
            if (!(c_file.attrib & _A_SUBDIR))
                count++;
        } while (_findnext(hFile, &c_file) == 0);
        _findclose(hFile);
    }
    return count;
}

// ������ ������.
file_info* all_files(const char* path, size_t* len)
{
    struct _finddata_t c_file;
    intptr_t hFile;
    file_info* file;
    int index;
    *len = count_files(path);
    index = 0;
    if (*len == 0 || (hFile = _findfirst(path, &c_file)) == -1L)
        return NULL;
    file = (file_info*)malloc(sizeof(file_info) * *len);
    do
    {
        if (!(c_file.attrib & _A_SUBDIR))
        {
            if (index >= *len)
                break;
            file_info data;
            data.name = strdup(c_file.name);
            data.time_write = c_file.time_write;
            data.size = c_file.size;
            file[index++] = data;
        }
    } while (_findnext(hFile, &c_file) == 0);
    _findclose(hFile);
    return file;
}

// ������������ ������ ����� ������� ������.
void memory_clear(file_info* file, size_t len)
{
    size_t i;
    for (i = 0; i < len; i++)
        free(file[i].name);
    free(file);
}

// ������� ��� ��������� �������� ������� ��� ����������.
// ��� � ���� ����� ��������� ��� ��������.
void swap_i(file_info* file, int i, int j)
{
    file_info temp;
    temp = file[i];
    file[i] = file[j];
    file[j] = temp;
}

// ������������ ������ �� ��������.
void descending_order(file_info* file, int len)
{
    int i;
    for (i = 0; i < len / 2; i++)
        swap_i(file, i, len - i - 1);
}

// ���������� ��������� ������ ������������ � ����
int scan_methods(int* result, int min_v, int max_v)
{
    int methods;
    methods = scanf_s("%d", result);
    while (getchar() != '\n');
    if (methods == 1 && *result >= min_v && *result <= max_v)
        return 1;
    return 0;
}

// ���������� ������� ��������
int bubble(file_info* file, int len)
{
    int i;
    int j;
    int swaps;
    for (i = 0; i < len - 1; i++)
    {
        swaps = 0;
        for (j = 0; j < len - i - 1; j++)
        {
            if (file[j].size > file[j + 1].size)
            {
                swap_i(file, j, j + 1);
                swaps++;
            }
        }
        if (swaps == 0)
            break;
    }
    return 1;
}

// ���������� ������� ������
int selection(file_info* file, int len)
{
    int i, j, min_index;
    _fsize_t min_size;
    for (i = 0; i < len; i++)
    {
        min_index = i;
        min_size = file[i].size;
        for (j = i + 1; j < len; j++)
        {
            if (file[j].size < min_size)
            {
                min_index = j;
                min_size = file[j].size;
            }
        }
        swap_i(file, i, min_index);
    }
    return 1;
}

// ���������� ������� �������
int insertion(file_info* file, int len)
{
    int i, j;
    file_info current_element;
    for (i = 1; i < len; i++)
    {
        current_element = file[i];
        j = i - 1;
        while (j >= 0 && file[j].size > current_element.size)
        {
            file[j + 1] = file[j];
            --j;
        }
        file[j + 1] = current_element;
    }
    return 1;
}

// ������� ��������.
// ����� ��������, ������ ���, ����� ��, ��� �����.
int array_merge(file_info* file, int low_b, int split_i, int up_b)
{
    int left_index, right_index, merge_index;
    file_info* temp;
    left_index = low_b;
    right_index = split_i;
    merge_index = 0;
    temp = (file_info*)malloc(sizeof(file_info) * (up_b - low_b));
    if (temp == NULL)
        return 0;
    while (left_index < split_i && right_index < up_b)
    {
        if (file[left_index].size < file[right_index].size)
            temp[merge_index++] = file[left_index++];
        else
            temp[merge_index++] = file[right_index++];
    }
    while (right_index < up_b)
        temp[merge_index++] = file[right_index++];
    while (left_index < split_i)
        temp[merge_index++] = file[left_index++];
    for (merge_index = 0; merge_index < up_b - low_b; merge_index++)
        file[low_b + merge_index] = temp[merge_index];
    free(temp);
    return 1;
}

// ���������� ������� �������.
int merging(file_info* file, int low_b, int up_b)
{
    int success;
    int split;
    if (up_b - low_b > 1)
    {
        split = (low_b + up_b) / 2;
        merging(file, low_b, split);
        merging(file, split, up_b);
        success = array_merge(file, low_b, split, up_b);
        if (!success)
            return 0;
    }
    return 1;
}

// ���������� ������� �����.
int hoare_sort(file_info* file, int len)
{
    int i = 0;
    int j = len - 1;
    _fsize_t center_size;

    center_size = file[len >> 1].size;
    do {
        while (file[i].size < center_size)
            i++;
        while (file[j].size > center_size)
            j--;

        if (i <= j)
        {
            swap_i(file, i, j);
            i++;
            j--;
        }
    } while (i <= j);
    if (j > 0)
        hoare_sort(file, j + 1);
    if (len > i)
        hoare_sort(file + i, len - i);
}

// ���������� ������� �����.
int shell_sort(file_info* file, int len)
{
    int s, i, j;
    file_info current_element;
    for (s = len / 2; s > 0; s /= 2)
    {
        for (i = s; i < len; ++i)
        {
            current_element = file[i];
            j = i - 1;
            while (j >= 0 && file[j].size > current_element.size)
            {
                file[j + 1] = file[j];
                --j;
            }
            file[j + 1] = current_element;
        }
    }
    return 1;
}

// ���������� ������� ��������.
int counting(file_info* file, int len)
{
    int i;
    int* counts;
    _fsize_t j;
    _fsize_t max_size = 0;
    file_info* temp;
    for (i = 0; i < len; i++)
    {
        if (file[i].size > max_size)
            max_size = file[i].size;
    }
    counts = (int*)calloc(max_size + 1, sizeof(int));
    if (counts == NULL)
        return 0;
    for (i = 0; i < len; i++)
        counts[file[i].size]++;
    for (j = 1; j <= max_size; j++)
        counts[j] += counts[j - 1];
    temp = (file_info*)malloc(sizeof(file_info) * len);
    if (temp == NULL)
    {
        free(counts);
        return 0;
    }
    for (i = 0; i < len; i++)
    {
        temp[counts[file[i].size] - 1] = file[i];
        counts[file[i].size]--;
    }
    for (i = 0; i < len; i++)
        file[i] = temp[i];
    free(counts);
    free(temp);
    return 1;
}

// ���� ����������.
void sort_menu(char path[MAX_PATH_LENGTH + 1])
{
    int sort;
    int method_1;
    int method_2;
    size_t count;
    file_info* file;
    time_t begin, end;
    double total_time;
    char buffer_t[30];
    do
    {
        system("cls");
        printf("��������� �������� ����������:\n1) ���������\n2) �������\n3) ��������\n4) ��������\n5) �����(�������)\n6) �����\n7) ���������\n8) ��������� � ����\n"
            "������� �������� ������� (����� �� 1 �� 8): ");
    } while (!scan_methods(&method_1, 1, 8));
    if (method_1 == 8)
        return;
    file = all_files(path, &count);
    begin = clock();
    do
    {
        system("cls");
        printf("����� ������� ���������� ����������?\n1) �� �����������\n2) �� ��������\n3) ��������� � ����\n"
            "������� �������� ������� (����� 1 ��� 3): ");
    } while (!scan_methods(&method_2, 1, 3));
    if (method_2 == 3)
        return;
    switch (method_1)
    {
    case 1:
        sort = bubble(file, count);
        break;
    case 2:
        sort = selection(file, count);
        break;
    case 3:
        sort = insertion(file, count);
        break;
    case 4:
        sort = merging(file, 0, count);
        break;
    case 5:
        sort = hoare_sort(file, count);
        break;
    case 6:
        sort = shell_sort(file, count);
        break;
    case 7:
        sort = counting(file, count);
        break;
    case 8:
        sort = backup_menu(method_1);
        break;
    }
    switch (method_2)
    {
    case 1:
        break;
    case 2:
        descending_order(file, count);
        break;
    case 3:
        return;
    }
    end = clock();
    total_time = (double)(end - begin) / CLOCKS_PER_SEC;
    if (!sort)
        printf("�� ������� ������������� �����!\n");
    else
    {
        system("cls");
        printf("����                 ����                          ������\n"
            "______________________________________________________________\n");
        for (int i = 0; i < count; i++)
        {
            ctime_s(buffer_t, _countof(buffer_t), &(file[i].time_write));
            printf("%-20.20s %.24s  %10lu ����\n", file[i].name, buffer_t, file[i].size);
        }
        if (count == 0)
            printf("�������, ��� ������ ���. ���������� ������� ������ ����.\n");
        printf("����� ����������: %lfsec\n", total_time);
    }
    memory_clear(file, count);
    system("pause");
}

// ���� ��������.
void menu(char path[MAX_PATH_LENGTH + 1])
{
    int read_line; // ���������� ����
    int options; // ����� ������������
    do
    {
        printf("������! ��� �������� ��������� ���������.\n����� �� ������ ����� ����� � ����������� � ������������� �� ������� ���������.\n"
            "���� ���������� �������� ���� � ������. ������ - D:\\�����1\\�����2\\�����3\\*.*\n"
            "������ ���� � ������ �����: ");
        read_line = scanf("%" STR(MAX_PATH_LENGTH) "[^\n]", path);
        system("cls");
        while (getchar() != '\n');
    } while (read_line != 1);


    while (1)
    {

        do
        {
            system("cls");
            printf("����:\n1) �������� ���� � ������\n2) ����� ������ ����������\n3) ����� �� ���������\n"
                "������� �������� ������� (����� �� 1 �� 3): ");

        } while (!scan_methods(&options, 1, 3));
        system("cls");
        switch (options)
        {
        case 1: // ������ �������� ����
            menu(path);
            system("cls");
            break;
        case 2: // ��������� � ���� ����������
            sort_menu(path);
            system("cls");
            break;
        case 3: // ��������� ���������
            return;
        }
    }
}

// ����, ������� ���������� ��� ������ ���� �����.
int backup_menu(int method)
{
    system("cls");
    char path[MAX_PATH_LENGTH + 1]; // �������� ������� ��� ���� � ������
    menu(path);
};

// �������� ���������, ������� ��������� �� ������ ����, � ����� � ����.
// � ���� ������� � ���� ���� �������, ������� ��������� �� ���� � ������� ����������.
int main(void)
{
    char path[MAX_PATH_LENGTH + 1]; // �������� ������� ��� ���� � ������
    SetConsoleCP(1251); // ������� ���� ��� �������
    SetConsoleOutputCP(1251); // ������� ���� ��� �������
    menu(path); // ��������� ���� ���������
}
