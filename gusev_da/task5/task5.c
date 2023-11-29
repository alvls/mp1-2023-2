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

// Создаём структуру с информацией о файле, где будет записаны название, дата и размер.
typedef struct
{
    char* name;
    time_t time_write;
    _fsize_t size;
} file_info;

// Выявляет количество файлов в пути.
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

// Список файлов.
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

// Освобождение памяти после прогона файлов.
void memory_clear(file_info* file, size_t len)
{
    size_t i;
    for (i = 0; i < len; i++)
        free(file[i].name);
    free(file);
}

// Функция для изменения индексов местами при сортировке.
// Так в разы проще проводить эту операцию.
void swap_i(file_info* file, int i, int j)
{
    file_info temp;
    temp = file[i];
    file[i] = file[j];
    file[j] = temp;
}

// Расположение файлов по убыванию.
void descending_order(file_info* file, int len)
{
    int i;
    for (i = 0; i < len / 2; i++)
        swap_i(file, i, len - i - 1);
}

// Считывание вариантов ответа пользователя в меню
int scan_methods(int* result, int min_v, int max_v)
{
    int methods;
    methods = scanf_s("%d", result);
    while (getchar() != '\n');
    if (methods == 1 && *result >= min_v && *result <= max_v)
        return 1;
    return 0;
}

// Сортировка методом пузырька
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

// Сортировка методом выбора
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

// Сортировка методом вставок
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

// Слияние массивов.
// Вынес отдельно, потому что, опять же, так проще.
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

// Сортировка методом слияния.
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

// Сортировка методом Хоара.
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

// Сортировка методом Шелла.
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

// Сортировка методом подсчёта.
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

// Меню сортировки.
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
        printf("Возможные варианты сортировки:\n1) Пузырьком\n2) Выбором\n3) Вставкой\n4) Слиянием\n5) Хоара(быстрая)\n6) Шелла\n7) Подсчетом\n8) Вернуться в меню\n"
            "Введите желаемый вариант (цифра от 1 до 8): ");
    } while (!scan_methods(&method_1, 1, 8));
    if (method_1 == 8)
        return;
    file = all_files(path, &count);
    begin = clock();
    do
    {
        system("cls");
        printf("Каким образом произвести сортировку?\n1) По возрастанию\n2) По убыванию\n3) Вернуться в меню\n"
            "Введите желаемый вариант (цифра 1 или 3): ");
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
        printf("Не удалось отсортировать файлы!\n");
    else
    {
        system("cls");
        printf("Файл                 Дата                          Размер\n"
            "______________________________________________________________\n");
        for (int i = 0; i < count; i++)
        {
            ctime_s(buffer_t, _countof(buffer_t), &(file[i].time_write));
            printf("%-20.20s %.24s  %10lu байт\n", file[i].name, buffer_t, file[i].size);
        }
        if (count == 0)
            printf("Кажется, что файлов нет. Попробуйте выбрать другой путь.\n");
        printf("Время сортировки: %lfsec\n", total_time);
    }
    memory_clear(file, count);
    system("pause");
}

// Меню основное.
void menu(char path[MAX_PATH_LENGTH + 1])
{
    int read_line; // Считывание пути
    int options; // Выбор пользователя
    do
    {
        printf("Привет! Это прототип файлового менеджера.\nЗдесь ты можешь найти файлы в директориях и отсортировать их разными способами.\n"
            "Тебе необходимо вставить путь к файлам. Пример - D:\\Папка1\\Папка2\\Папка3\\*.*\n"
            "Вставь путь к файлам здесь: ");
        read_line = scanf("%" STR(MAX_PATH_LENGTH) "[^\n]", path);
        system("cls");
        while (getchar() != '\n');
    } while (read_line != 1);


    while (1)
    {

        do
        {
            system("cls");
            printf("Меню:\n1) Изменить путь к файлам\n2) Выбор метода сортировки\n3) Выход из программы\n"
                "Введите желаемый вариант (цифра от 1 до 3): ");

        } while (!scan_methods(&options, 1, 3));
        system("cls");
        switch (options)
        {
        case 1: // Заново выбираем путь
            menu(path);
            system("cls");
            break;
        case 2: // Переходим к меню сортировки
            sort_menu(path);
            system("cls");
            break;
        case 3: // Выключаем программу
            return;
        }
    }
}

// Меню, которое включается при выборе шага назад.
int backup_menu(int method)
{
    system("cls");
    char path[MAX_PATH_LENGTH + 1]; // Создание массива для пути к файлам
    menu(path);
};

// Основная программа, которая ссылается на чтение пути, а затем и меню.
// В свою очередь в меню есть функция, которая ссылается на меню с выбором сортировки.
int main(void)
{
    char path[MAX_PATH_LENGTH + 1]; // Создание массива для пути к файлам
    SetConsoleCP(1251); // Русский язык для консоли
    SetConsoleOutputCP(1251); // Русский язык для консоли
    menu(path); // Включение меню программы
}
