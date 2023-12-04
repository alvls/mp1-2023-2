#include <stdio.h>
#include <conio.h>
#include <io.h>  
#include <omp.h>  
#include <locale.h>
#include <string.h>
#include "sort.h"
#include "Menu.h"
#include "print_info.h"

int main()
{
    setlocale(LC_ALL, "rus");

    struct _finddata_t c_file;
    intptr_t hFile;

    struct file_info* files = malloc(5000 * sizeof(struct file_info));

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
                struct file_info* copy = malloc(5000 * sizeof(struct file_info));
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


