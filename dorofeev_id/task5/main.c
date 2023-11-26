#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "sorts.h"
#include <locale.h>



int main()
{
    setlocale(LC_ALL, "rus");
    char path[] = "D:\\VS\\source\\repos\\mp1-2023-2\\mp1-2023-2\\dorofeev_id\\task5\\*.*";
    int file_count;
    file* lol = get_files(path, &file_count);

    if (lol == NULL) {
        // Handle memory allocation failure
        printf("Memory allocation failed!\n");
        return 1;
    }

    print_files(lol, file_count);
    printf("\n%d", file_count);
    printf("\n\n\ncomplete");

    bubble_size(lol, file_count, 1);
    print_files(lol, file_count);

    selection_size(lol, file_count, 1);
    print_files(lol, file_count);

    insertion_size(lol, file_count, 1);
    print_files(lol, file_count);

    merge_sort(lol, 0, file_count - 1, 1);
    print_files(lol, file_count);

    shell_size(lol, file_count, 1);
    print_files(lol, file_count);

    counting_size(lol, file_count, 1);
    print_files(lol, file_count);

    hoar_size(lol, file_count, 1);
    print_files(lol, file_count);

    free(lol);

    return 0;
}

