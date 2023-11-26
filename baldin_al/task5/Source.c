#include <stdio.h>
#include <conio.h>
#include <stdlib.h>  
#include <io.h>  
#include <omp.h>  
#include <time.h>
#include <locale.h>
#include <string.h>
#include <memory.h>

#define UP 72
#define DOWN 80
#define ENTER 13

int sort_id = -1;
int type_of_sort = -1;

struct file_info {
    char name[256];
    unsigned long size;
    time_t time_create;
    time_t time_access;
    time_t time_write;
};

void list_of_files(struct file_info* files, int count);
void BubbleSort(struct file_info* files, int size);
void SelectSort(struct file_info* files, long size);
void InsertSort(struct file_info* files, long size);
void Merge(struct file_info* files, long lb, long split, long ub);
void MergeSort(struct file_info* files, long lb, long ub);
void HoareSort(struct file_info* files, long N);
int increment(long inc[], long size);
void ShellSort(struct file_info* files, long size);
void CountingSort(struct file_info* files, int size);

char* menu[5][80] = {
 "Вывести информацию о файлах",
 "Выбрать метод сортировки",
 "Выбрать тип сортировки",
 "Отсортировать",
 "Exit"
};

char* submenu[2][7][20] = {
    {"1) Пузырьком","2) Выбором", "3) Вставками", "4) Слиянием", "5) Хоара", "6) Шелла", "7) Подсчётом"},
    {"По возрастанию","По убыванию"},
};


void printMenu(int selected, char* menu[20], int count) {
    for (int i = 0; i < count; i++) {
        if (i == selected) {
            printf("\033[31m%s\n\033[0m", menu[i]);
        }
        else {
            printf("%s\n", menu[i]);
        }
    }
}

void Sub_Menu(int choice) {
    if (choice == 1)
    {
        int subchoice = 0;
        while (1) {
            system("cls");
            printMenu(subchoice, submenu[choice - 1], 7);
            char c = getch();
            if (c == UP) {
                subchoice--;
                if (subchoice < 0)
                    subchoice = 7 + subchoice;
            }
            else if (c == DOWN) {
                subchoice++;
                subchoice = subchoice % 7;
            }
            else if (c == ENTER) {
                break;
            }
        }
        sort_id = subchoice;
    }
    else
    {
        int subchoice = 0;
        while (1) {
            system("cls");
            printMenu(subchoice, submenu[choice - 1], 2);
            char c = getch();
            if (c == UP) {
                subchoice--;
                if (subchoice < 0)
                    subchoice = 2 + subchoice;
            }
            else if (c == DOWN) {
                subchoice++;
                subchoice = subchoice % 2;
            }
            else if (c == ENTER) {
                break;
            }
        }
        type_of_sort = subchoice;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");

    struct _finddata_t c_file;
    intptr_t hFile;

    struct file_info* files = malloc(1000 * sizeof(struct file_info));

    int i = 0; // количество файлов
    double start, end;
    double time;
    printf("Для того, чтобы перемещаться между пунктами меню и подменю, используйте стрелки клавиатуры.\n");
    printf("Чтобы выбрать пункт или операцию нажмите ENTER.\n\n");
    printf("Введите полный путь до директории: ");
    char dir[_MAX_PATH + 1];
    gets_s(dir, sizeof(dir));
    char search[_MAX_PATH + 4 + 1];
    strcpy_s(search, sizeof(search), dir);
    strcat_s(search, sizeof(search), "\\*.*");
    search[_MAX_PATH + 4] = '\0';

    hFile = _findfirst(search, &c_file);

    if (hFile != -1L) {
        do {
            if (c_file.name[0] == '.')
                continue;
            strcpy_s(files[i].name, sizeof(files[i].name), c_file.name);
            files[i].size = c_file.size;
            files[i].time_create = c_file.time_create;
            files[i].time_access = c_file.time_access;
            files[i].time_write = c_file.time_write;
            i++;
        } while (_findnext(hFile, &c_file) == 0);
        _findclose(hFile);
    }
    else
    {
        printf("В данной директории не существует или в ней отсутствуют файлы");
        exit(0);
    }

    int choice = 0;
    char next = ENTER;
    do {
        system("cls");
        printMenu(choice, menu, 5);
        char c = getch();
        if (c == UP) {
            choice--;
            if (choice < 0)
                choice = 5 + choice;
        }
        else if (c == DOWN) {
            choice++;
            choice = choice % 5;
        }
        else if (c == ENTER && choice == 0)
        {
            list_of_files(files, i);
        }
        else if (c == ENTER && (choice == 1 || choice == 2)) {
            Sub_Menu(choice);
        }
        else if (c == ENTER && choice == 3)
        {
            if (sort_id == -1 || type_of_sort == -1)
            {
                char ch;
                printf("Укажите все параметры сортировки \n");
                printf("Чтобы вернуться к настройке сортировки нажмите Enter");
                do {
                    ch = _getch();
                } while (ch != ENTER);
            }
            else
            {
                struct file_info* copy = malloc(1000 * sizeof(struct file_info));
                for (int n = 0; n < i; n++)
                {
                    copy[n] = files[n];
                }
                start = omp_get_wtime();
                switch (sort_id) {
                case 0:
                    BubbleSort(copy, i);
                    break;
                case 1:
                    SelectSort(copy, i);
                    break;
                case 2:
                    InsertSort(copy, i);
                    break;
                case 3:
                    MergeSort(copy, 0, i - 1);
                    break;
                case 4:
                    HoareSort(copy, i - 1);
                    break;
                case 5:
                    ShellSort(copy, i);
                    break;
                case 6:
                    CountingSort(copy, i);
                    break;
                }
                end = omp_get_wtime();
                time = end - start;
                if (type_of_sort == 0)
                {
                    for (int j = 0; j < i; j++)
                    {
                        printf("%-12.12s  %10ld\n", copy[j].name, copy[j].size);
                    }
                }
                else
                {
                    for (int j = i - 1; j >= 0; j--)
                    {
                        printf("%-12.12s  %10ld\n", copy[j].name, copy[j].size);
                    }
                }
                printf("--------------------------------------");
                printf("\n Время выполнения сортировки: %.15f \n\n", time);
                printf("Если вы хотите выбрать другой метод или тип сортировки, то нажмите ENTER. \n");
                printf("Если нет, то любую другую клавишу \n");
                next = _getch();
                free(copy);
            }
        }
        else if (c == ENTER && choice == 4)
            break;
    } while (next == ENTER);
    free(files);
    return 0;
}

void list_of_files(struct file_info* files, int count)
{
    printf("FILE         TIME CREATE %13c TIME ACCESS %13c TIME WRITE %16c SIZE\n", ' ', ' ', ' ');
    printf("----         ----------- %13c ----------- %13c ---------- %16c ----\n", ' ', ' ', ' ');
    for (int i = 0; i < count; i++) {
        char buffer1[30];
        char buffer2[30];
        char buffer3[30];
        ctime_s(buffer1, _countof(buffer1), &files[i].time_create);
        ctime_s(buffer2, _countof(buffer2), &files[i].time_access);
        ctime_s(buffer3, _countof(buffer3), &files[i].time_write);
        printf("%-12.12s %.24s  %.24s  %.24s %10ld\n", files[i].name, buffer1, buffer2, buffer3, files[i].size);
    }
    char ch;
    printf("\n Чтобы вернуться к настройке сортировки нажмите Enter");
    do {
        ch = _getch();
    } while (ch != ENTER);
}

void BubbleSort(struct file_info* files, int size)
{
    long i, j;
    struct file_info temp;
    for (i = 0; i < size; i++)
    {
        for (j = size - 1; j > i; j--)
        {
            if (files[j - 1].size > files[j].size)
            {
                temp = files[j - 1];
                files[j - 1] = files[j];
                files[j] = temp;
            }
        }
    }
}

void SelectSort(struct file_info* files, long size)
{
    long i, j, k;
    struct file_info temp;

    for (i = 0; i < size; i++)
    {
        k = i; temp = files[i];

        for (j = i + 1; j < size; j++)
            if (files[j].size < temp.size)
            {
                k = j; temp = files[j];
            }

        files[k] = files[i]; files[i] = temp;
    }
}

void InsertSort(struct file_info* files, long size)
{
    struct file_info temp;
    long i, j;

    for (i = 0; i < size; i++)
    {
        temp = files[i];
        for (j = i - 1; j >= 0 && files[j].size > temp.size; j--)
            files[j + 1] = files[j];
        files[j + 1] = temp;
    }
}

void Merge(struct file_info* files, long lb, long split, long ub)
{
    long pos1 = lb;
    long pos2 = split + 1;
    long pos3 = 0;
    struct file_info* temp = malloc(sizeof(struct file_info) * (ub - lb + 1));
    while (pos1 <= split && pos2 <= ub)
    {
        if (files[pos1].size < files[pos2].size)
            temp[pos3++] = files[pos1++];
        else
            temp[pos3++] = files[pos2++];
    }
    while (pos2 <= ub)
        temp[pos3++] = files[pos2++];
    while (pos1 <= split)
        temp[pos3++] = files[pos1++];
    for (pos3 = 0; pos3 < ub - lb + 1; pos3++)
        files[lb + pos3] = temp[pos3];

    free(temp);
}
void MergeSort(struct file_info* files, long lb, long ub)
{
    long split;

    if (lb < ub)
    {
        split = (lb + ub) / 2;

        MergeSort(files, lb, split);
        MergeSort(files, split + 1, ub);
        Merge(files, lb, split, ub);
    }
}

void HoareSort(struct file_info* files, long N)
{
    long i = 0, j = N - 1;
    struct file_info temp, q;

    q = files[N >> 1];
    do {
        while (files[i].size < q.size)
            i++;
        while (files[j].size > q.size)
            j--;

        if (i <= j)
        {
            temp = files[i]; files[i] = files[j]; files[j] = temp;
            i++;
            j--;
        }
    } while (i <= j);
    if (j > 0)
        HoareSort(files, j + 1);
    if (N > i)
        HoareSort(files + i, N - i);
}

int increment(long inc[], long size)
{
    int p1, p2, p3, s;
    p1 = p2 = p3 = 1;
    s = -1;
    do {
        if (++s % 2)
        {
            inc[s] = 8 * p1 - 6 * p2 + 1;
        }
        else
        {
            inc[s] = 9 * p1 - 9 * p3 + 1;
            p2 *= 2;
            p3 *= 2;
        }
        p1 *= 2;
    } while (3 * inc[s] < size);
    return s > 0 ? --s : 0;
}

void ShellSort(struct file_info* files, long size)
{
    long inc, i, j, seq[40];
    int s;
    s = increment(seq, size);
    while (s >= 0)
    {
        inc = seq[s--];

        for (i = inc; i < size; i++)
        {
            struct file_info temp = files[i];
            for (j = i - inc; (j >= 0) && (files[j].size > temp.size); j -= inc)
                files[j + inc] = files[j];
            files[j + inc] = temp;
        }
    }
}

void CountingSort(struct file_info* files, int size)
{
    int max_value = 0;
    for (int i = 0; i < size; i++)
    {
        if (files[i].size > max_value)
            max_value = files[i].size;
    }
    struct file_info* c = (struct file_info*)malloc((max_value + 1) * sizeof(struct file_info));
    memset(c, 0, sizeof(*files) * (max_value + 1));

    for (int i = 0; i < size; ++i) {
        ++c[files[i].size].size;
        strcpy_s(c[files[i].size].name, sizeof(c[files[i].size].name), files[i].name);

    }

    int b = 0;
    for (int i = 0; i < max_value + 1; ++i)
    {
        for (int j = 0; j < c[i].size; ++j)
        {
            files[b++].size = i;
            strcpy_s(files[b - 1].name, sizeof(files[b - 1].name), c[i].name);
        }
    }
    free(c);
}