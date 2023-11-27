#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "sorts.h"
#include <locale.h>
#include <windows.h>

void measure_time(void (*sort_func)(file*, int, int), file* files, int amount, int order, const char* sort_name)
{
    LARGE_INTEGER start_time, end_time, frequency;
    double elapsed_time;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start_time);

    // Sort function call
    sort_func(files, amount, order);

    QueryPerformanceCounter(&end_time);

    elapsed_time = ((double)(end_time.QuadPart - start_time.QuadPart)) / frequency.QuadPart;

    printf("Time taken by %s: %f seconds\n", sort_name, elapsed_time);
}



int main()
{
    setlocale(LC_ALL, "rus");

    char path[256] = "c:/*.*";
    int file_count;
    file* lol = get_files(path, &file_count);

    if (lol == NULL) {
        // Handle memory allocation failure
        printf("Memory allocation failed!\n");
        return 1;
    }

    int action;
    int fl;
    int order;
    int type;
    int by;

    while (1 == 1)
    {
        printf("What do you want to do?\n");
        printf("1 - output the list of files\n");
        printf("2 - sort files\n");
        printf("3 - clear the console\n");
        printf("4 - change directory\n");
        printf("5 - terminate the program\n");


        scanf("%d", &action);
        switch (action)
        {
        case 1:
            print_files(lol, file_count);
            break;

        case 2:
            fl = 1;
            while (fl == 1)
            {
                printf("Choose an order of sort\n");
                printf("1 - ascending\n");
                printf("2 - descending\n");

                scanf("%d", &order);
                switch (order)
                {
                case 1:
                    printf("Sort will be ascending\n");
                    fl = 0;
                    break;

                case 2:
                    printf("Sort will be descending\n");
                    fl = 0;
                    break;

                default:
                    printf("There is no such order. Try again\n");
                    break;
                }
            }

            fl = 1;
            while (fl == 1)
            {
                printf("Sort by SIZE or by NAME\n");
                printf("1 - by SIZE\n");
                printf("2 - by NAME\n");

                scanf("%d", &by);
                switch (by)
                {
                case 1:
                    printf("Sorting by SIZE\n");
                    fl = 0;
                    break;

                case 2:
                    printf("Sorting by NAME\n");
                    fl = 0;
                    break;

                default:
                    printf("There is no such parameter. Try again\n");
                    break;
                }
            }

            fl = 1;
            while (fl == 1)
            {
                printf("Choose type of sort\n");
                printf("1 - Bubble\n");
                printf("2 - Selection\n");
                printf("3 - Insertion\n");
                printf("4 - Merge\n");
                printf("5 - Shell\n");
                printf("6 - Counting\n");
                printf("7 - Hoar\n");

                scanf("%d", &type);
                switch (type)
                {
                case 1:
                    if (by == 1)
                    {
                        measure_time(bubble_size, lol, file_count, order, "Bubble Sort by size");
                        fl = 0;
                        break;
                    }
                    else
                    {
                        measure_time(bubble_name, lol, file_count, order, "Bubble Sort by name");
                        fl = 0;
                        break;
                    }

                case 2:
                    if (by == 1)
                    {
                        measure_time(selection_size, lol, file_count, order, "Selection Sort by size");
                        fl = 0;
                        break;
                    }
                    else
                    {
                        measure_time(selection_name, lol, file_count, order, "Selection Sort by name");
                        fl = 0;
                        break;
                    }

                case 3:
                    if (by == 1)
                    {
                        measure_time(insertion_size, lol, file_count, order, "Insertion Sort by size");
                        fl = 0;
                        break;
                    }
                    else
                    {
                        measure_time(insertion_name, lol, file_count, order, "Insertion Sort by name");
                        fl = 0;
                        break;
                    }

                case 4:
                    if (by == 1)
                    {
                        merge_sort_size(lol, 0, file_count - 1, order);
                        measure_time(merge_sort_size, lol, file_count, order, "Merge Sort by size");
                        fl = 0;
                        break;
                    }
                    else
                    {
                        merge_sort_name(lol, 0, file_count - 1, order);
                        measure_time(merge_sort_name, lol, file_count, order, "Merge Sort by name");
                        fl = 0;
                        break;
                    }

                case 5:
                    if (by == 1)
                    {
                        measure_time(shell_size, lol, file_count, order, "Shell Sort by size");
                        fl = 0;
                        break;
                    }
                    else
                    {
                        measure_time(shell_name, lol, file_count, order, "Counting Sort by name");
                        fl = 0;
                        break;
                    }

                case 6:
                    if (by == 1)
                    {
                        measure_time(counting_size, lol, file_count, order, "Counting Sort by size");
                        fl = 0;
                        break;
                    }
                    else
                    {
                        printf("Counting sort could be used only for sorting by size. Choose other sort type\n");
                        break;
                    }

                case 7:
                    if (by == 1)
                    {
                        measure_time(hoar_size, lol, file_count, order, "Hoar Sort by size");
                        fl = 0;
                        break;
                    }
                    else
                    {
                        measure_time(hoar_name, lol, file_count, order, "Hoar Sort by name");
                        fl = 0;
                        break;
                    }

                default:
                    printf("There is no such type. Try again.");
                    break;
                }
            }

            break;

        case 3:
            system("cls");
            break;

        case 4:
            printf("Enter the path; Use / as the folder separator, be sure to add *.* at the end(Example: C:/Temp/*.*)\n");
            scanf("%s", path);
            lol = get_files(path, &file_count);
            break;

        case 5:
            free(lol);
            return 0;

        default:
            printf("There is no such action. Try again\n");
            break;
        }
    }

    return 0;
}

